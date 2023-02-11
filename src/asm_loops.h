#include <stdio.h>
#include <stdbool.h>

#ifndef WELL_ASM_LOOPS_H
#define WELL_ASM_LOOPS_H

struct loop_data {

    char *INS_FOR_LAT;

};

int while_interp(FILE *out, char line[], int line_num, int whilenum_ln,
                 const char *fname, const char *funcname, int whilenum, bool is_in_if);

int for_interp(FILE *out, char line[], int line_num, int fornum_ln,
               const char *fname, const char *funcname, int fornum, bool is_in_if);

#endif
