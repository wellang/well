/*Copyright (c) 2024 Tristan Wellman*/
#ifndef WDATA_H
#define WDATA_H

#include "util.h"
#include "../include/argparse.h"

typedef struct {
	FILE *main;
	char *fileName;
	struct ArgparseParser argParser;	
	
	int KEEPASM, USEINFO, USELD, COBJ;
	char *outputFile;
	char *ccFlags;
	char *ldflags;
} wData;

#endif
