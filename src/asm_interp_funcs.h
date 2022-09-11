#include <stdio.h>

#ifndef ASM_INTERP_FUNCS_H
#define ASM_INTERP_FUNCS_H

int asm_interp_var_funcs(char line[], FILE *out, int line_num, const char *fname);
int asm_interp_func_funcs(char line[], FILE *out, int line_num, const char *fname);

#endif
