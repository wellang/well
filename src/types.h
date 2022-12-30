/*Copyright 2022 Tristan Wellman*/
#include <stdio.h>

#ifndef TYPES_H
#define TYPES_H

struct mut_data {
  const char *muts[sizeof(int)];
  int number_of_mutables;
};

int string_interp(const char *fname, char line[], int line_num, FILE *out);
const char *mut_interp(char line[], int line_num);
int length_interp(char line[], FILE *out);
int int_interp(const char *fname, char line[], int line_num, FILE *out);
/*int _floa_interp_(char line[], FILE *out)*/
int char_interp(const char *fname, FILE *out, char line[], int line_num);
int array_run(FILE *out, char line[]);

#endif
