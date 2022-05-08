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

	FILE *file2 = fopen(fname, "r+");
	char line3[256];
	int line_num1 = 0;
	while(fgets(line3, sizeof(line3), file2) != NULL) {

		char search[] = "r~func:main {";
                char *func = strstr(line3, search);

		if(func != NULL) {
			FILE *outputfunc = fopen("a.asm", "a");
			fprintf(outputfunc, "global _start\n\n_start:\n\t");
			fclose(outputfunc);

			FILE *funcread = fopen(fname, "r+");
			char mainline[256];
			int line_num2 = 0;
			while(fgets(mainline, sizeof(mainline), funcread) != NULL) {
				
				FILE *out;
				char end[] = "}";
				
				if(line_num2 == line_num1) {
					if(mainline == NULL) {
						break;
					} else if(mainline == end) {
						break;
					} else {
						mov_interp(mainline, out);
						push_interp(mainline, out);
						syscall_interp(mainline, out);
					}
					line_num1++;
				}
				line_num2++;
				//line_num1++;
			}
			//fclose(funcread);
		}	

		if(line3 == NULL) {
			break;
		}
		line_num1++;	

	}

	fclose(file2);
	FILE *file3 = fopen(fname, "r+");
	char line4[256];
	int line_num = 0;
	while(fgets(line4, sizeof(line4), file3) != NULL) {

		char search[] = "v~func:";
		char *func = strstr(line4, search);

		if(func != NULL) {
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
										
									//line_num++;
									file_line++;
								}

								if(line5 == NULL) {
									break;
								} else if(line5 == "func:main {") {
									break;
								} else if(line5 == "func:main ") {
									break;
								} else if(line5 == "func:main") {
									break;
								}
								
								line_num++;
							}
							fclose(funcread);		
						} else if(func_name == "main") {
							continue;
						} else if(func_name == "main ") {
							continue;
						} else if(func_name == "main {") {
							continue;
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
				} else if(after_func == "main {") {
					continue;
				} else if(after_func == "main ") {
					continue;
				} else if(after_func == "main") {
					continue;
				}
		} else if(func == NULL) {
			continue;
		} else if(line4 == "func:main") {
			continue;
		} else if(line4 == "func:main {") {
			continue;
		} else if(line4 == "func:main ") {
			continue;
		}
		line_num++;
		if(line4 == NULL) {
			break;
		}

	}

	//fclose(file);
	//fclose(output);
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
