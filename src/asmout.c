/*Copyright (c) 2024 Tristan Wellman*/

#include "asmout.h"

void freeAsm(AsmOut *out) {
	fclose(out->asmOut);
	free(out->functions);
}

void initAsmOut(struct parserData *parser, AsmOut *output) {
	output->parser = parser;
	int i;
	output->functions = (Function *)malloc(sizeof(Function)*parser->totalFunctions);

	char fbuf[100];
	snprintf(fbuf, sizeof(fbuf), "%s.s", parser->fData->fileName);
	output->asmOut = fopen(fbuf, "wr");

	/*Don't forget output buffer is in parser->output.asmOutBuffer*/
}
