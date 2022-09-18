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

	//char FUNC_NAME[];

} include_file;

int include_var_funcs(char line[], FILE *out, int line_num, const char *fname) {

	string_interp(line, out);
	length_interp(line, out);
	int_interp(line, out);

	char_interp(out, line);
	print_asm_interp(out, line, line_num, fname);
	
	return 0;

}

int include_func_funcs(char line[], FILE *out, int line_num, const char *fname, const char *funcname, int ifnum) {

	if_interp(out, line, line_num, fname, funcname, ifnum);
	if_end_interp(out, line, line_num, fname, funcname, ifnum);

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
//	run_interp(out, line);
//	call_interp(out, line);
	call_func(out, line);
	print_asm_interp(out, line, line_num, fname);
	lea_interp(line, out, line_num);
	return0(out, line, line_num, fname);

	return 0;

}

	/*
	 *include: call~ wellfile.wellfunc
	 *include_lib: lib~ wellfile.wellfunc
	 * */


const char *get_asm_name(const char *fname, const char *final_name) {

	

	return final_name;

}

int include_comp(FILE *out, char line[], int line_num, const char *fname, const char *funcname, int callnum) {

	char call[] = "call~ ";
	char mov[] = "move~ ";

	char *find_call = strstr(line, call);
	if(find_call != NULL) {
		char tild[] = "~"; 
		char *file_and_func = strstr(line, tild); //wellfile.wellfunc

		if(file_and_func != NULL) {
			file_and_func++;
		}

		//log_info(":%s:", file_and_func);
		
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
			//printf(line0);

			if(line0 == NULL) {
				break;
			}

			char *func_find = strstr(line0, func_buf);
			if(func_find != NULL) {
				//log_info(line0);
				int func_line = line_num;
				char line1[256];

				int ifnum = 9999;

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
							if(iffind != NULL) {ifnum++;}
							include_func_funcs(line1, out, func_line, fname, funcname, ifnum);
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

		
		fclose(include_file.wellfile);

	} else {
		return 0;
	}

	return 0;
}

int lib_comp(const char *fname) {
	
	

	return 0;
}



