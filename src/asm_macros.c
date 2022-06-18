/*Copyright (c) 2022 Tristan Wellman*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mov_search.h"
#include "syscall_interp.h"
#include "push_search.h"
#include "types.h"
#include "instructions.h"
#include "log.h"

int macro_interp(const char *fname) {

	FILE *file = fopen(fname, "r+");
	char line[256];
	int line_num = 0;

	while(fgets(line, sizeof(line), file) != NULL) {
		
		line_num++;

		char search[] = "~macro:";
		char *macro = strstr(line, search);

		if(macro != NULL) {
			log_info("Found macro at line: %d\n", line_num);
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

					while(fgets(line, sizeof(line), read) != NULL) {
						if(line_better != line_line) {
							line_better++;
						} else if(line_better == line_line) {
							line_line++;
							line_better++;
							char *macro_end = strstr(line, "}");
							char *func = strstr(line, "~func:");
							if(func != NULL) {
								log_info("line:%d macro compiler found function\n", line_better);
								break;
							} else if(macro_end != NULL) {
								log_info("line:%d macro compiler found end of vars, macros, or functions\n", line_better);
								continue;
							} else if(func == NULL && macro_end == NULL) {
								FILE *out;
								mov_interp(line, out);
								push_interp(line, out);
								syscall_interp(line, out);
								pop_interp(out, line);
								array_run(out, line);
								cif_interp(out, line);
								halt_interp(out, line);
								bits_interp(out, line);
								print_asm_interp(out, line);
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
					while(fgets(line, sizeof(line), read) != NULL) {
						if(line_better != line_line) {
							line_better++;
						} else if(line_better == line_line) {
							line_line++;
							line_better++;
							char *macro_end = strstr(line, "}");
							char *func = strstr(line, "~func:");
							if(func != NULL) {
								log_info("line:%d macro compiler found function\n", line_better);
								break;
							} else if(macro_end != NULL) {
								log_info("line:%d macro compiler found end of vars, marcros, or functions\n", line_better);
								continue;
							} else if(func == NULL && macro_end == NULL) {
								FILE *out;
								mov_interp(line, out);
								push_interp(line, out);
								syscall_interp(line, out);
								pop_interp(out, line);	
								array_run(out, line);
								cif_interp(out, line);
								halt_interp(out, line);
								bits_interp(out, line);
								print_asm_interp(out, line);
							}
						}

					}

				}
			} else {
				log_error("Macro missing name and/or ':' delimeter!\n");
				return 0;
			}
		} 

	}
	
	FILE *end = fopen("a.asm", "a");
	fprintf(end, "\n%%endmacro\n");
	fclose(end);

	return 0;
}
