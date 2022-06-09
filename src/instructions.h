#include <stdio.h>
#ifndef INTRUCTIONS_H
#define INSTRUCTIONS_H

int pop_interp(FILE *out, char line[]);
int call_interp(FILE *out, char line[]);
int ret_interp(FILE *out, char line[]);
int cif_interp(FILE *out, char line[]);
int halt_interp(FILE *out, char line[]);
int bits_interp(FILE *out, char line[]);
int run_interp(FILE *out, char line[]);
int print_asm_interp(FILE *out, char line[]);
int resb_interp(FILE *out, char line[]);

#endif
