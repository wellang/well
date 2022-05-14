#include <stdio.h>
#ifndef INTRUCTIONS_H
#define INSTRUCTIONS_H

int pop_interp(FILE *out, char line[]);
int call_interp(FILE *out, char line[]);
int ret_interp(FILE *out, char line[]);

#endif
