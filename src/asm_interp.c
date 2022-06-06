#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mov_search.h"
#include "syscall_interp.h"
#include "push_search.h"
#include "types.h"
#include "log.h"
#include "instructions.h"

int asm_interp(int argc, char *argv[]) {

	const char *fname;

	fname = argv[1];
	char line[256];

	FILE *file;
	file = fopen(fname, "r+");
	FILE *output;
	output = fopen("a.asm", "a");

	fprintf(output, "section .data ;variables & data not implimented yet\n\n"/*section .text\n\n"*/);
	fclose(output);
	
	FILE *file6 = fopen(fname, "r+");
	char line7[256];

	while(fgets(line7, sizeof(line7), file6) != NULL) {
		
		char include_search[] = "include~ ";
		char *include = strstr(line7, include_search);

		if(include != NULL) {
			
		}
		if(line7 == NULL) {
			break;
		}

	}

	while(fgets(line, sizeof(line), file) != NULL) {
				
		char var_search[] = "var:main {";
		char *var = strstr(line, var_search);

		if(var != NULL) {
			FILE *out2;
			FILE *varread = fopen(fname, "r+");
			char mainlines[256];

			while(fgets(mainlines, sizeof(mainlines), varread) != NULL) {
				if(mainlines == NULL) {
					break;
				} else {
					string_interp(mainlines, out2);
					length_interp(mainlines, out2);
					int_interp(mainlines, out2);
				}
			}

		}
	
		if(line == NULL) {
			break;
		}
	}
	
	FILE *out3 = fopen("a.asm", "a");
	fprintf(out3, "section .text\n\n");
	fclose(out3);

	FILE *file3 = fopen(fname, "r+");
	char line4[256];
	int line_num = 0;
	int lineline_num = 0;
	while(fgets(line4, sizeof(line4), file3) != NULL) {
		
		lineline_num++;
		char search[] = "~func:";
		char *func = strstr(line4, search);
		char search_main[] = "~func:main"; 
		char *main = strstr(line4, search_main);

		if(func != NULL && main == NULL) {
				log_info("found function at line: %d", lineline_num);
				char *after_func = strchr(line4, ':');
				if(after_func != NULL) {
						after_func++;
						
						char search[] = "{";
						char *brack = strstr(after_func, search);
						if(brack != NULL) {
							char *function_name = strtok(after_func, "{");
							FILE *func = fopen("a.asm", "a");
							function_name[strlen(function_name)-1] = '\0';
							fprintf(func, "%s:\n", function_name);
							fclose(func);

							FILE *read = fopen(fname, "r+");
							char line6[256];
							int line_better = 0;
							int line_line = line_num;
							while(fgets(line6, sizeof(line6), read) != NULL) {
								if(line_better != line_line) {
									line_better++;
								} else if(line_better == line_line) {
									line_better++;
									line_line++;
									char *end = strstr(line6, "}");
									char *main = strstr(line6, "func:main");
									if(end != NULL) {
										printf("line:%d is the end of a function\n", line_better);
										continue;
									} else if(main != NULL) {
										printf("line:%d found main function\n", line_better);
										break;
									} else if(end == NULL && main == NULL){
										FILE *out;
										mov_interp(line6, out);
										push_interp(line6, out);
										syscall_interp(line6, out);
										pop_interp(out, line6);
										array_run(out, line6);
									}
								}
							}	
						} else if(brack == NULL) {
							log_warn("sub function brackets not implimented yet\n\n");
						}

				} else if(after_func == NULL) {
						log_error("ERROR:: Line.%d - Function does not have delimiter ':'\n", line_num);
						continue;
				}
		} else if(func != NULL && main != NULL) {
			log_info("found main fuction at line: %d", lineline_num);
      			FILE *outputfunc = fopen("a.asm", "a");
	                fprintf(outputfunc, "\n\nglobal _start\n\n_start:\n\t");
 	                fclose(outputfunc);

			FILE *main_func = fopen(fname, "r+");
			char mainline[256];
			int mainline_num = 0;
			int line_line = line_num;
			while(fgets(mainline, sizeof(mainline), main_func) != NULL) {
				if(mainline_num != line_line) {
					mainline_num++;
				} else if(mainline_num == line_line) {
					line_line++;
					mainline_num++;
					char *main_search = strstr(mainline, "func:main");
					if(main_search != NULL) {
						int the_line = mainline_num;
						int line_yo = 0;
						FILE *main_run = fopen(fname, "r+");
						char lineline[256];
						while(fgets(lineline, sizeof(lineline), main_run) != NULL) {
							
							if(line_yo != the_line) {
								line_yo++;
								continue;
							} else if(line_yo == the_line) {
								line_yo++;
								the_line++;

								char *main_search = strstr(lineline, "func:main");
								char *end_of_main = strstr(lineline, "}");
								if(end_of_main != NULL && main_search == NULL) {
									break;	
								} else if(end_of_main == NULL && main_search == NULL) {
									FILE *out;
									mov_interp(lineline, out);
									push_interp(lineline, out);
									syscall_interp(lineline, out);
									pop_interp(out, lineline);
								}

							}
						}
					} else if(main_search == NULL) {
						continue;
					}
				}
				if(mainline == NULL) {
					break;
				}
			}
			fclose(main_func);

		} else if(func == NULL && main == NULL) {
			continue;
		}
		line_num++;
		if(line4 == NULL) {
			break;
		}

	}

	/*fclose(file);*/
	/*fclose(output);*/
	return 0;

}

void compile(int argc, char *argv[]) {

	char buf[0x100];
	char *arg = "-o";
	const char *OUTPUT_NAME;
	const char *EXEC_NAME;

	if(argv[2] == arg) {
		OUTPUT_NAME = argv[3];
		EXEC_NAME = argv[4];
		snprintf(buf, sizeof(buf), "nasm -f elf64 a.asm -o %s && ld %s -o %s && rm -f %s", OUTPUT_NAME, OUTPUT_NAME, EXEC_NAME, OUTPUT_NAME);
		system(buf);
		log_info("%s Compiled successfully!\n", OUTPUT_NAME);
	} else {
		system("nasm -f elf64 a.asm -o a.o && ld a.o -o out");
		log_info("Program Compiled successfully!\n");
	}

}

int main(int argc, char *argv[]) {

	if(argv[1] == NULL) {
		log_error("\n:: Invalid file name, ex: wesm (.well file) -o (.o file) (executable name)\n > wesm test.well -o test.o test\n\n");
		return 0;
	}

	asm_interp(argc, argv);
	compile(argc, argv);
	return 0;	

}
