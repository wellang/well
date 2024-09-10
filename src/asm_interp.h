#ifndef ASM_INTERP_H
#define ASM_INTERP_H

#include "util.h"

struct wellFileData {
	FILE *input;
	FILE *output;

	char *input_name;
};

#endif
