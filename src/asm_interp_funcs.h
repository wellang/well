#include <stdio.h>
#include <stdbool.h>

#ifndef ASM_INTERP_FUNCS_H
#define ASM_INTERP_FUNCS_H

int asm_interp_var_funcs(char line[], FILE *out, int line_num, const char *fname);
int asm_interp_func_funcs(char line[], FILE *out, int line_num, int ifnum_ln,
                          const char *fname, const char *funcname, int ifnum,
                          int callnum, bool is_in_if);

#endif
