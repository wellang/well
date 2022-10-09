#include <stdio.h>
#ifndef ASM_MACROS_H
#define ASM_MACROS_H

int macro_call_interp(char line[], const char *fname, int line_num);
int macro_interp(const char *fname);

#endif
