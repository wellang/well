#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "mov_search.h"
#include "syscall_interp.h"
#include "push_search.h"
#include "types.h"
#include "log.h"
#include "instructions.h"
#include "asm_macros.h"
#include "lea.h"
#include "if.h"
#include "include.h"

#include "libwesm/com.h"

#define call_func(file, line)	\
        char search[] = "call~ ";	\
        char *call = strstr(line, search);	\
        if(call != NULL) {	\
        	call++;	\
		call++;	\
		call++;	\
		call++;	\
		call++;	\
		call++;	\
                out = fopen("a.asm", "a");	\
                fprintf(out, "\n\tcall %s", call);	\
                fclose(out);	\
        }	\

struct include_file {

	FILE *wellfile;


} include_file;

int include_var_funcs(char line[], FILE *out, int line_num, const char *fname) {

	string_interp(line, out);
	int_interp(line, out);

	char_interp(out, line);
	print_asm_interp(out, line, line_num, fname);
	
	return 0;

}

int include_func_funcs(char line[], FILE *out, int line_num, int ifnum_ln,
					   const char *fname, const char *funcname, int ifnum, bool is_in_if) {

	if_interp(out, line, line_num, ifnum_ln, fname, funcname, ifnum, is_in_if);
	if_end_interp(out, line, line_num, ifnum_ln, fname, funcname, ifnum);

	mov_interp(line, out, line_num, fname);
	add_interp(out, line, line_num, fname);
	sub_interp(out, line, line_num, fname);
	push_interp(line, out);
	
	syscall_interp(line, out);
	pop_interp(out, line, line_num, fname);
	array_run(out, line);
	cif_interp(out, line, line_num, fname);
	halt_interp(out, line, line_num, fname);
	bits_interp(out, line, line_num, fname);
	call_func(out, line);
	print_asm_interp(out, line, line_num, fname);
	lea_interp(line, out, line_num);
	return0(out, line, line_num, fname);

	return 0;

}

	/*
	 *include: call~ wellfile.wellfunc
	 *include_lib: libcall~ wellfile.wellfunc
	 * */

void file_lib_include_vars_and_macros_comp(const char *fname) {

	FILE *file = fopen(fname, "r");
	char line[256];

	bool comment_check;

	while(fgets(line, sizeof(line), file) != NULL) {

		comment_check = __check_com__(line);
		if(comment_check == true) {
			continue;
		}

		char var_search[] = "~var:main {";
		char *var = strstr(line, var_search);

		if(var != NULL) {
			FILE *out2;
			FILE *varread = fopen(fname, "r");
			char mainlines[256];
			int lnum = 0;
			while(fgets(mainlines, sizeof(mainlines), varread) != NULL) {

				comment_check = __check_com__(mainlines);
				if(comment_check == true) {
					continue;
				}

				lnum++;
				char *search_b = strstr(mainlines, "}");
				if(search_b != NULL) {
					break;
				}
				if(mainlines == NULL) {
					break;
				} else {
					include_var_funcs(mainlines, out2, lnum, fname);
				}

			}
		}

	}

	file_lib_include_comp(fname);

	FILE *out3 = fopen("a.asm", "a");
	fprintf(out3, "\nsection .text\n\n");
	fclose(out3);

	macro_interp(fname);

}

int file_lib_include_comp(const char *fname) {

	/*
	  NOTE: This function is meant to be used before functions are compiled & after vars
	  */

	int retval = 0;

	FILE *file = fopen(fname, "r");
	char line[256];
	int line_num = 0;

	while(fgets(line, sizeof(line), file) != NULL) {

		line_num++;

		char *include_ = strstr(line, "~include <");
		if(include_ != NULL) {

			retval = 1;

			include_++;

			char *afterc = strstr(include_, "<");
			if(afterc != NULL) {
				afterc++;
				const char delim[] = ">";
				char *filename = strtok(afterc, delim);
				if(file != NULL) {

					  char buf[0x100];
#if defined __WIN32 | defined __WIN64 | defined __WIN32__
            snprintf(buf, sizeof(buf), "C:\\wesm\\libwesm\\%s", filename);
            printf("\n%s\n", buf);
#else
					  snprintf(buf, sizeof(buf), "/usr/include/wellang/libwesm/%s", filename);
#endif
					  file_lib_include_vars_and_macros_comp(buf);

				} else {
					wlog_error(fname, line_num, "include missing file");
					return 1;
				}
			} else {
				wlog_error(fname, line_num, "include missing file");
				return 1;
			}

		} else {
			continue;
		}

	}

	return retval;

}

int include_comp(FILE *out, char line[], int line_num, const char *fname,
				 const char *funcname, int callnum) {

	char call[] = "call~ ";
	char mov[] = "move~ ";

	char *find_call = strstr(line, call);
	if(find_call != NULL) {
		char tild[] = "~"; 
		char *file_and_func = strstr(line, tild);

		if(file_and_func != NULL) {
			file_and_func++;
		}

		const char delim[] = ".";
		char *func = strchr(file_and_func, '.');	
		char *file = strtok(file_and_func, delim);
		if(func != NULL) {
			func++;
		}
		func[strcspn(func, "\n")] = 0;	
		if(file != NULL) {
			file++;
		}

		wlog_info(fname, line_num, ":%s:%s:", func, file);
		
		char fname_buf[0x100];
		snprintf(fname_buf, sizeof(fname_buf), "%s.well", file);

		include_file.wellfile = fopen(fname_buf, "r+");
		char line0[256];

		if(include_file.wellfile == NULL) {
		
			wlog_error(fname_buf, line_num, "Invalid call file %s", file);
			return 1;
		
		}

		char func_buf[0x100];
		snprintf(func_buf, sizeof(func_buf), "~func:%s", func);

		time_t t;
		srand((unsigned) time(&t));
		int r = rand() % 9999;

		int rando = r;
		FILE *out1 = fopen("a.asm", "a");
		char buff[0x100];
		/*
		   call func.1234func
		   jmp func.123funcfin
		   .1234func:
		   mov rdi, rsi
		   .123funcfin:
		   rest of code
		*/
		snprintf(buff, sizeof(buff), "\n\tjmp %s._%d%s_\n\tjmp %s._%d%s_fin\n\t._%d%s_:",
				funcname, callnum, func,
				funcname, callnum, func,
				 callnum, func);
		fprintf(out1, buff);
		fclose(out1);

		int line_num = 0;
		while(fgets(line0, sizeof(line0), include_file.wellfile) != NULL) {
			line_num++;

			if(line0 == NULL) {
				break;
			}

			char *func_find = strstr(line0, func_buf);
			if(func_find != NULL) {
				int func_line = line_num;
				char line1[256];

				int ifnum = 9999;
				bool is_in_if = false;
				int ifnum_ln = 0;

				while(fgets(line1, sizeof(line1), include_file.wellfile) != NULL) {
					func_line++;

					if(line1 == NULL) {
						return 0;
					}
					if(func_line >= line_num) {
						char search[] = "}";
						char *brack = strstr(line1, search);
						if(brack != NULL) {
							break;
						} else {
							FILE *out;
							char *iffind = strstr(line1, "~if");
							if(iffind != NULL) {
								ifnum_ln = func_line;
								ifnum++;
								FILE *if_ = fopen(fname, "r+");
								is_in_if = IS_IN_IF(if_, func_line, fname);
							}
							include_func_funcs(line1,
											   out,
											   func_line,
											   ifnum_ln,
											   fname,
											   funcname,
											   ifnum,
											   is_in_if);
						}
					} else if(func_line < line_num) {
						continue;
					}
				}
				continue;
			}


		}
		FILE *out2 = fopen("a.asm", "a");
		char bufff[0x100];
		snprintf(bufff, sizeof(bufff), "\n\tjmp %s._%d%s_fin\n\t._%d%s_fin:\n", 
				funcname, callnum, func,
				callnum, func);
		fprintf(out2, bufff);
		fclose(out2);

		
		fclose(include_file.wellfile);

	} else {
		return 0;
	}

	return 0;
}

int lib_comp(FILE *out, char line[], int line_num, const char *fname, const char *funcname, int callnum) {
	
	char lcall[] = "libcall~ ";
	char *lcall_s = strstr(line, lcall);

	if(lcall_s != NULL) {
		char tild[] = "~";
		char *file_and_func = strstr(line, tild);

		if(file_and_func != NULL) {file_and_func++;} else {
			wlog_error(fname, line_num, "MISSING lib file &/or function!\n");
			return 1;
		}

		const char delim[] = ".";
		char *func = strchr(file_and_func, '.');
		char *file = strtok(file_and_func, delim);
		if(func != NULL) {func++;} else {
			wlog_error(fname, line_num, "MISSING lib function after file name!\n");
			return -1;
		}
		if(file != NULL) {file++;} else {
			wlog_error(fname, line_num, "MISSING lib file name before function!\n");
			return -1;
		}
		func[strlen(func)-1] = '\0';

		char fname_buf[0x100];
		/*#ifndef _WIN32

		     wlog_warn(fname, line_num, "Support for windows libcalls are unfinished!\n");
		     snprintf(fname_buf, sizeof(fname_buf), "%s.well", file);

        #else*/

		printf("%s\n%s", file, func);
		snprintf(fname_buf, sizeof(fname_buf), "/usr/include/wellang/libwesm/%s.well", file);

		include_file.wellfile = fopen(fname_buf, "r");
		char line0[0x256];

		if(include_file.wellfile == NULL) {
			wlog_error(fname, line_num, "INVALID libcall file &/or you are on windows!\n");
			return 1;
		}

		char func_buf[0x100];
		snprintf(func_buf, sizeof(func_buf), "~func:%s", func);

		FILE *out1 = fopen("a.asm", "a");

		char buff[0x100];
		snprintf(buff, sizeof(buff), "\n\tjmp %s._%d%s_\n\tjmp %s._%d%s_fin\n\t._%d%s_:",
				 funcname, callnum, func,
				 funcname, callnum, func,
				 callnum, func);

		fprintf(out1, buff);
		fclose(out1);

		int line_num = 0;
		while(fgets(line0, sizeof(line0), include_file.wellfile) != NULL) {

			line_num++;

			if(line0 == NULL) {
				break;
			}

			char *func_find = strstr(line0, func_buf);
			if(func_find != NULL) {

				int func_line = line_num;
				char line1[256];

				int ifnum = 1999;
				bool is_in_if = false;
				int ifnum_ln = 0;

				while(fgets(line1, sizeof(line1), include_file.wellfile) != NULL) {

					func_line++;

					if(line1 == NULL) {
						return 0;
					}

					if(func_line >= line_num) {

						char search[] = "}";
						char *brack = strstr(line1, search);

						if(brack != NULL) {
							break;
						} else {
							FILE *out;
							char *iffind = strstr(line1, "~if");
							if(iffind != NULL) {
								ifnum++;
								ifnum_ln = func_line;
								FILE *if_ = fopen(fname, "r+");
								is_in_if = IS_IN_IF(if_, func_line, fname);
							}
							include_func_funcs(line1,
											   out,
											   func_line,
											   ifnum_ln,
											   fname,
											   funcname,
											   ifnum,
											   is_in_if);
						}
					} else if(func_line < line_num) {
						continue;
					}
				}
				continue;
			}
		}

		FILE *out2 = fopen("a.asm", "a");
		char bufff[0x100];
		snprintf(bufff, sizeof(bufff), "\n\t._%d%s_fin:\n", callnum, func);
		fprintf(out2, bufff);
		fclose(out2);

	} else {
			return 0;
	}

	return 0;
}



