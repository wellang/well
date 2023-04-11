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
#include "if.h"

#include "libwesm/com.h"
bool comment_check_;

int macro_call_interp(char line[], const char *fname, int line_num) {

	/*the ultimate replacement for all instruction functions
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
  char *if_ = strstr(line, "~if");
  char *if_end_ = strstr(line, "~end");
  if(if_ != NULL) { return 0; }
  if(if_end_ != NULL) { return 0; }

	if(tild != NULL) {

		const char delim[] = "~";
		char *aftertild = strchr(line, '~');
		char *before = strtok(line, delim);

		if(aftertild != NULL) {
			aftertild++;
		} else {
			wlog_error(fname, line_num, "Unfinished macro call\n"
                                        "       |\n"
                                        "   %d|\t%s\n", line_num, line);
			return 1;
		}

		if(before != NULL && aftertild != NULL) {

			while(isspace(*before)) {
				before++;
      }

			if(before[0] == ' ') {
				return 0;
			}

			char macro[0x100];
			snprintf(macro, sizeof(macro), "%%macro %s", before);
      
			FILE *fil = fopen("a.asm", "r");
			char lineee[256];
			int linenum = 0;

			while(fgets(lineee, sizeof(lineee), fil)) {

				if(lineee == NULL) { break; } else { linenum++; }

			}
			FILE *file = fopen("a.asm", "r");
			char linee[256];
			int lnum = 0;

			while(fgets(linee, sizeof(linee), file) != NULL) {

				lnum++;

				if(lnum == linenum) {
					return 1;
				}

				char *findmac = strstr(linee, macro);
				if(findmac != NULL) {

					snprintf(string, sizeof(string), "\n\t%s %s", before, aftertild);
					string[strlen(string)-1] = '\0';
					FILE *aasm = fopen("a.asm", "a");
					fprintf(aasm, string);
					fclose(aasm);
					break;

				}
			}
			return 0;
		} else {
			return 0;
		}

	} else {
		return 0;
	}

	return 0;
}

int macro_interp(const char *fname) {

	FILE *file = fopen(fname, "r");
	char line[256];
	int line_num = 0;
	int lineline_num = 0;

	while(fgets(line, sizeof(line), file) != NULL) {

		comment_check_ = __check_com__(line);
		if(comment_check_ == true) {
			continue;
		}

		lineline_num++;

		char search[] = "~macro:";
		char *macro = strstr(line, search);

		if(macro != NULL) {
			/*wlog_info(fname, line_num, "Found macro\n");*/
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

					/*macro_name[strlen(macro_name)-1] = '\0';*/
					FILE *mac = fopen("a.asm", "a");
					fprintf(mac, "\n%%macro %s %s\n", macro_name, arg_num);
					fclose(mac);

					FILE *read = fopen(fname, "r");
					char line[256];
					int line_line = lineline_num;
					int line_better = 0;

					int ifnum = 1010101;
					bool is_in_if = false;
					int ifnum_ln = 0;

					int callnum = 0;

					while(fgets(line, sizeof(line), read) != NULL) {

						comment_check_ = __check_com__(line);
						if(comment_check_ == true) {
							continue;
						}

						if(line_better != line_line) {
							line_better++;
						} else if(line_better == line_line) {
							line_better++;
							line_line++;
							char *macro_end = strstr(line, "}");
							char *func = strstr(line, "~func:");
							if(func != NULL) {
								break;
							} else if(macro_end != NULL) {
								break;
							} else if(func == NULL && macro_end == NULL) {
								FILE *out;
								char *callfind = strstr(line, "call~");

								char *iffind = strstr(line, "~if");
								if(iffind != NULL) {
									ifnum++;
									ifnum_ln = line_better;
									FILE *if_ = fopen(fname, "r");
									is_in_if = IS_IN_IF(if_, line_better, fname);
								}

								if(callfind != NULL) {callnum++;}
								syscall_interp(line, out);
								print_asm_interp(out, line, line_better, fname);
								call_interp(out, line, line_num, fname, macro_name, callnum);
								macro_call_interp(line, fname, line_better);
							}
						}
					}

				} else {
					/*macro with no args?*/
					char *macro_name = strtok(after_macro, "{");
					FILE *mac = fopen("a.asm", "a");

					fprintf(mac, "\n%%macro %s\n", macro_name);
					fclose(mac);

					FILE *read = fopen(fname, "r");
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
								break;
							} else if(macro_end != NULL) {
								break;
							} else if(func == NULL && macro_end == NULL) {
								FILE *out;
								char *callfind = strstr(line, "call~");
								if(callfind != NULL) {callnum++;}
								syscall_interp(line, out);
								print_asm_interp(out, line, line_better, fname);
								call_interp(out, line, line_better, fname, macro_name, callnum);
								macro_call_interp(line, fname, line_better);
							}
						}

					}

				}
			} else {
				wlog_error(fname, line_num, "Macro missing name and/or ':' delimeter!\n"
                                            "       |\n"
                                            "   %d|\t%s\n", line_num, line);
				return 0;
			}
	        	FILE *end = fopen("a.asm", "a");
	        	fprintf(end, "\n%%endmacro\n");
        		fclose(end);
		} 

		line_num++;

	}
	
	return 0;
}
