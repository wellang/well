#include <stdio.h>
#ifndef INTRUCTIONS_H
#define INSTRUCTIONS_H

int pop_interp(FILE *out, char line[], int line_num, const char *fname);
int call_interp(FILE *out, char line[], int line_num, const char *fname);
int ret_interp(FILE *out, char line[], int line_num, const char *fname);
int cif_interp(FILE *out, char line[], int line_num, const char *fname);
int halt_interp(FILE *out, char line[], int line_num, const char *fname);
int bits_interp(FILE *out, char line[], int line_num, const char *fname);
int run_interp(FILE *out, char line[], int line_num, const char *fname);
int print_asm_interp(FILE *out, char line[], int line_num, const char *fname);
int resb_interp(FILE *out, char line[], int line_num, const char *fname);
int return0(FILE *out, char line[], int line_num, const char *fname);

#endif
