/*Copyright (c) 2024 Tristan Wellman*/

#include "asmout.h"

/*
 * Instruction conversion
 * */

/*
 * Run
 * */

void convertToAsm(AsmOut *out) {
	
}


/*
 * Initialization & exiting
 * */

int getRoughFileSize(AsmOut *out) {
	return out->parser->bufferSize*2;
}

void freeAsm(AsmOut *out) {
	fclose(out->asmOut);
	free(out->functions);
}

void initAsmOut(struct parserData *parser, AsmOut *output) {
	output->parser = parser;
	int i;
	output->functions = (Function *)malloc(sizeof(Function)*parser->totalFunctions);

	char *fileName = strtok(parser->fData->fileName, ".");
	strcat(fileName, ".s");

	output->asmOut = fopen(fileName, "r");
	/*File already exists*/
	if(output->asmOut!=NULL) {
		char rm[100];
		snprintf(rm, sizeof(rm), "rm %s", fileName);
		system(rm);
	} 
	fclose(output->asmOut);
	
	/*reopen with write mode/create file*/
	output->asmOut = fopen(fileName, "wr");

	int roughEstimate = getRoughFileSize(output);
	output->parser->output.asmOutBuffer = (char *)malloc(sizeof(char)*roughEstimate);

	/*Don't forget output buffer is in parser->output.asmOutBuffer*/
}


