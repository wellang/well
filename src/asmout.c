/*Copyright (c) 2024 Tristan Wellman*/

#include "asmout.h"

/*
 * Instruction conversion
 * */

/* This should be pretty standard along all CPUs
 * Variable conversion
 * */

void convertVariables(AsmOut *out) {

}

/*
 * Run
 * */

void initHeader(AsmOut *out) {
	char *standardHead = 
		"\t.section __TEXT,__text\n\t.global _main\n\t.p2align 2\n";
	out->buffers.heading = (char *)malloc(sizeof(char)*strlen(standardHead));
	strcpy(out->buffers.heading, standardHead);
}

void convertToAsm(AsmOut *out) {
	initHeader(out);
	convertVariables(out);
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
	output->buffers.output.asmOutBuffer = (char *)malloc(sizeof(char)*roughEstimate);
	output->buffers.output.AOBSize = 0;

	/*Don't forget output buffer is in parser->output.asmOutBuffer*/
}


