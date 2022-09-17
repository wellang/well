#include <stdio.h>

#ifndef IF_H_
#define IF_H_

int if_interp(FILE *out, char line[], int line_num, const char *fname, const char *funcname, int ifnum);
int if_end_interp(FILE *out, char line[], int line_num, const char *fname, const char *funcname, int ifnum);

#endif // IF_H_
