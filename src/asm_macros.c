/*Copyright (c) 2022 Tristan Wellman*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mov_search.h"
#include "syscall_interp.h"
#include "push_search.h"
#include "types.h"
#include "instructions.h"
#include "lea.h"
#include "log.h"

#include "libwesm/com.h"
bool comment_check_;

int macro_call_interp(char line[], const char *fname, int line_num) {

	// the ultimate replacement for all instruction functions

	/*
	*
	*  ~macro:move[2] {
	*    asm~ mov %%2, %%1
	*  }
    *
	*  ~func:main {
	*     move~ 1, rax
	*  }
	*
	 */

	char string[0x100];

	char *tild = strstr(line, "~");

	if(tild != NULL) {

		const char delim[] = "~";
		char *aftertild = strchr(line, '~');
		char *before = strtok(line, delim);

		if(aftertild != NULL) {
			aftertild++;
		} else {
			wlog_error(fname, line_num, "Unfinished macro call\n");
			return 1;
		}

		if(before != NULL && aftertild != NULL) {

			while(isspace(*before)) {
				before++;
			}

			char macro[0x100];
			snprintf(macro, sizeof(macro), "%%macro %s", before);
			wlog_info(fname, line_num, macro);

			FILE *fil = fopen("a.asm", "r+");
			char lineee[256];
			int linenum = 0;

			while(fgets(lineee, sizeof(lineee), fil)) {

				if(lineee == NULL) { break; } else { linenum++; }

			}

			FILE *file = fopen("a.asm", "r+");
			char linee[256];
			int lnum = 0;

			while(fgets(linee, sizeof(linee), file) != NULL) {

				lnum++;

				if(lnum == linenum) {
					wlog_error(fname, line_num, "Undefined reference to %s", before);
					return 1;
				}

				char *findmac = strstr(linee, macro);
				if(findmac != NULL) {

					snprintf(string, sizeof(string), "%s %s", before, aftertild);
					FILE *aasm = fopen("a.asm", "a");
					fprintf(aasm, string);
					fclose(aasm);
					break;

				}
			}
			return 0;
		}

	} else {
		return 0;
	}

	return 0;
}

int macro_interp(const char *fname) {

	FILE *file = fopen(fname, "r+");
	char line[256];
	int line_num = 0;

	while(fgets(line, sizeof(line), file) != NULL) {

		comment_check_ = __check_com__(line);
		if(comment_check_ == true) {
			continue;
		}

		line_num++;

		char search[] = "~macro:";
		char *macro = strstr(line, search);

		if(macro != NULL) {
			wlog_info(fname, line_num, "Found macro\n");
			char *after_macro = strchr(line, ':');
			if(after_macro != NULL) {
				after_macro++;
				/*well: ~macro:foo[2] {}
				 *nasm: %macro foo 2
				 	%endmacro*/
				char num_search[] = "[";
				char *brack = strstr(after_macro, num_search);
				if(brack != NULL) {
					char *macro_name = strtok(after_macro, "[");
					char *arg_bracks = strchr(after_macro, '[');
					char *arg_num = strtok(arg_bracks, "]");

					//macro_name[strlen(macro_name)-1] = '\0';
					FILE *mac = fopen("a.asm", "a");
					fprintf(mac, "%%macro %s %s\n", macro_name, arg_num);
					fclose(mac);

					FILE *read = fopen(fname, "r+");
					char line[256];
					int line_line = 0;
					int line_better = 0;

					int callnum = 0;

					while(fgets(line, sizeof(line), read) != NULL) {

						comment_check_ = __check_com__(line);
						if(comment_check_ == true) {
							continue;
						}

						if(line_better != line_line) {
							line_better++;
						} else if(line_better == line_line) {
							line_line++;
							line_better++;
							char *macro_end = strstr(line, "}");
							char *func = strstr(line, "~func:");
							if(func != NULL) {
								wlog_info(fname, line_better, "macro compiler found function\n");
								break;
							} else if(macro_end != NULL) {
								wlog_info(fname, line_better, "macro compiler found end of vars, macros, or functions\n");
								continue;
							} else if(func == NULL && macro_end == NULL) {
								FILE *out;
								char *callfind = strstr(line, "call~");
								if(callfind != NULL) {callnum++;}
								mov_interp(line, out, line_better, fname);
								add_interp(out, line, line_num, fname);
								sub_interp(out, line, line_num, fname);
								push_interp(line, out);
								syscall_interp(line, out);
								pop_interp(out, line, line_better, fname);
								array_run(out, line);
								cif_interp(out, line, line_better, fname);
								halt_interp(out, line, line_better, fname);
								bits_interp(out, line, line_better, fname);
								print_asm_interp(out, line, line_better, fname);
								lea_interp(line, out, line_num);
								call_interp(out, line, line_num, fname, macro_name, callnum);
								return0(out, line, line_num, fname);
							}
						}
					}

				} else {
					/*macro with no args?*/
					char *macro_name = strtok(after_macro, "{");
					FILE *mac = fopen("a.asm", "a");

					//macro_name[strlen(macro_name)-1] = '\0';
					fprintf(mac, "%%macro %s\n", macro_name);
					fclose(mac);

					FILE *read = fopen(fname, "r+");
					char line[256];
					int line_better = 0;
					int line_line = 0;

					int callnum = 0;

					while(fgets(line, sizeof(line), read) != NULL) {

						comment_check_ = __check_com__(line);
						if(comment_check_ == true) {
							continue;
						}

						if(line_better != line_line) {
							line_better++;
						} else if(line_better == line_line) {
							line_line++;
							line_better++;
							char *macro_end = strstr(line, "}");
							char *func = strstr(line, "~func:");
							if(func != NULL) {
								wlog_info(fname, line_better, " macro compiler found function\n");
								break;
							} else if(macro_end != NULL) {
								log_info(fname, line_better, "macro compiler found end of vars, marcros, or functions\n");
								continue;
							} else if(func == NULL && macro_end == NULL) {
								FILE *out;
								char *callfind = strstr(line, "call~");
								if(callfind != NULL) {callnum++;}
								mov_interp(line, out, line_better, fname);
								add_interp(out, line, line_better, fname);
								sub_interp(out, line, line_better, fname);
								push_interp(line, out);
								syscall_interp(line, out);
								pop_interp(out, line, line_better, fname);
								array_run(out, line);
								cif_interp(out, line, line_better, fname);
								halt_interp(out, line, line_better, fname);
								bits_interp(out, line, line_better, fname);
								print_asm_interp(out, line, line_better, fname);
								lea_interp(line, out, line_better);
								call_interp(out, line, line_better, fname, macro_name, callnum);
								return0(out, line, line_better, fname);
							}
						}

					}

				}
			} else {
				wlog_error(fname, line_num, "Macro missing name and/or ':' delimeter!\n");
				return 0;
			}
	        	FILE *end = fopen("a.asm", "a");
	        	fprintf(end, "\n%%endmacro\n");
        		fclose(end);
		} 

	}
	
	return 0;
}
