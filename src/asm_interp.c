#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mov_search.h"
#include "syscall_interp.h"

int asm_interp(int argc, char *argv[]) {

	const char *fname;

	fname = argv[1];
	char line[256];

	FILE *file;
	file = fopen(fname, "r+");
	FILE *output;
	output = fopen("a.asm", "a");

	fprintf(output, "section .data ;variables & data not implimented yet\n\nsection .text\n\n");
	fclose(output);

	while(fgets(line, sizeof(line), file) != NULL) {
		char search[] = "r:func:main {";
	       	char *func = strstr(line, search);

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
					syscall_interp(mainline, out);
				}

			}
			//fclose(funcread);
		}	

		if(line == NULL) {
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
