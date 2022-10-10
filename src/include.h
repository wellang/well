#include <stdio.h>
#include <stdbool.h>

#ifndef INCLUDE_H
#define INCLUDE_H

int include_var_funcs(char line[], FILE *out, int line_num, const char *fname);
int include_func_funcs(char line[], FILE *out, int line_num, int ifnum_ln,
                       const char *fname, const char *funcname, int ifnum,
                       bool is_in_if);

const char *get_asm_name(const char *fname, const char *final_name);

int file_lib_include_comp(const char *fname);
int include_comp(FILE *out, char line[], int line_num, const char *fname,
                 const char *funcname, int callnum);
int lib_comp(FILE *out, char line[], int line_num, const char *fname,
             const char *funcname, int callnum);

#endif
