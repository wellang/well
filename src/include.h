#ifndef INCLUDE_H
#define INCLUDE_H

int include_var_funcs(char line[], FILE *out);
int include_func_funcs(char line[], FILE *out, int line_num);

const char *get_asm_name(const char *fname, const char *final_name);

int include_comp(const char *fname);
int lib_comp(const char *fname);

#endif
