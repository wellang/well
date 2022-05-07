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
	while(fgets(line3, sizeof(line3), file2) != NULL) {

		char search[] = "r:func:main {";
                char *func = strstr(line3, search);

		if(func != NULL) {
			FILE *outputfunc = fopen("a.asm", "a");
			fprintf(outputfunc, "global _start\n\n_start:\n\t");
			fclose(outputfunc);

			FILE *funcread = fopen(fname, "r+");
			char mainline[256];
			while(fgets(mainline, sizeof(mainline), funcread) != NULL) {
				
				FILE *out;

				if(mainline == NULL) {
					break;
				} else {
					mov_interp(mainline, out);
					push_interp(mainline, out);
					syscall_interp(mainline, out);
				}

			}
			//fclose(funcread);
		}	

		if(line3 == NULL) {
			break;
		}	

	}

	//fclose(file);
	//fclose(output);
	return 0;

}

void compile(int argc, char *argv[]) {

	char buf[0x100];
	char arg[] = "-o";
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
