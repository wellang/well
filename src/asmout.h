/*Copyright (c) 2024 Tristan Wellman*/

#ifndef ASMOUT_H
#define ASMOUT_H
#include "util.h"
#include "werror.h"
#include "parser.h"

/*Parser data in asm form*/
typedef struct {

	FILE *asmOut;
	
	struct parserData *parser;

	/*malloc to total function length in parser*/
	Function *functions;

} AsmOut;

void convertToAsm(AsmOut *out); 
void freeAsm(AsmOut *out);
void initAsmOut(struct parserData *parser, AsmOut *output); 

#endif
