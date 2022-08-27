#include <stdio.h>

#ifndef TYPES_H
#define TYPES_H

int string_interp(char line[], FILE *out);
int length_interp(char line[], FILE *out);
int int_interp(char line[], FILE *out);
//int _floa_interp_(char line[], FILE *out)
int char_interp(FILE *out, char line[]);
int array_run(FILE *out, char line[]);

#endif
