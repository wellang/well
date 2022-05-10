#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mov_search.h"
#include "syscall_interp.h"
#include "push_search.h"
#include "types.h"

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
	while(fgets(line4, sizeof(line4), file3) != NULL) {

		char search[] = "~func:";
		char *func = strstr(line4, search);
		char search_main[] = "~func:main"; 
		char *main = strstr(line4, search_main);

		if(func != NULL && main == NULL) {
				char *after_func = strchr(line4, ':');
				if(after_func != NULL) {
						after_func++;
						char *func_name = strtok(after_func, "{");
						if(func_name != NULL) {
							FILE *funcread = fopen(fname, "r+");
							char line5[256];
							int file_line = 0;
							
							FILE *func_out = fopen("a.asm", "a");
							func_name[strlen(func_name)-1] = '\0';
							fprintf(func_out, "\n%s:\n", func_name);
							fclose(func_out);

							while(fgets(line5, sizeof(line5), funcread) != NULL) {
								
								if(file_line == line_num) {
									
									FILE *out;

									if(line5 != NULL) {
										mov_interp(line5, out);
										push_interp(line5, out);
										syscall_interp(line5, out);
									} else if(line5 == "}") {
										break;
									}
										
									/*line_num++;*/
									file_line++;
								}

								if(line5 == NULL) {
									break;
								}
								
								line_num++;
							}
							fclose(funcread);		
						} else {
							FILE *func_out = fopen("a.asm", "a");
							fprintf(func_out, "%s:\n", after_func);
							fclose(func_out);

							FILE *funcread = fopen(fname, "r+");
							char line6[256];
							int fline = 0;
							while(fgets(line6, sizeof(line6), funcread) != NULL) {
								
								if(fline == line_num) {
									FILE *out;

									if(line6 != NULL) {
										mov_interp(line6, out);
										push_interp(line6, out);
										syscall_interp(line6, out);
									} else if(line6 == "}") {
										break;
									}
									line_num++;
									fline++;
								}
								
								if(line6 == NULL) {
									break;
								}
								fline++;

							}

						}
				} else if(after_func == NULL) {
						printf("ERROR:: Line.%d - Function does not have delimiter ':'\n", line_num);
						continue;
				}
		} else if(func != NULL && main != NULL) {
      			FILE *outputfunc = fopen("a.asm", "a");
	                fprintf(outputfunc, "global _start\n\n_start:\n\t");
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
					char end_search[] = "}";
					char *end = strstr(mainline, end_search);
					FILE *out;
					if(end_search != NULL) {
						break;
					} else {
						mov_interp(mainline, out);
						push_interp(mainline, out);
						syscall_interp(mainline, out);
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
		printf("%s Compiled successfully!\n", OUTPUT_NAME);
	} else {
		system("nasm -f elf64 a.asm -o a.o && ld a.o -o out");
		printf("Program Compiled successfully!\n");
	}

}

int main(int argc, char *argv[]) {

	if(argv[1] == NULL) {
		printf("\n:: Invalid file name, ex: wesm (.well file) -o (.o file) (executable name)\n > wesm test.well -o test.o test\n\n");
		return 0;
	}

	asm_interp(argc, argv);
	compile(argc, argv);
	return 0;	

}
