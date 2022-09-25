#include <stdio.h>
#include <stdbool.h>

#ifndef IF_H_
#define IF_H_

int if_interp(FILE *out, char line[], int line_num, int ifnum_ln,
              const char *fname, const char *funcname, int ifnum,
              bool is_in_if);
int if_end_interp(FILE *out, char line[], int line_num, int ifnum_ln,
                  const char *fname, const char *funcname, int ifnum);

bool IS_IN_IF(FILE *file, int lnum, const char *fname);

#endif // IF_H_
