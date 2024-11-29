/*Copyright (c) 2024 Tristan Wellman*/

#include "asmout.h"

/* TODO
 * Instruction conversion
 * */

/* This should be pretty standard along all CPUs
 * Variable conversion
 * */

char *getAsmString(char *name, char *value) {
	static int strCount = 0;
	char buf[strlen(name)+strlen(value)+100];
	snprintf(buf, sizeof(buf),
			"wl_str.%s.%d:\n\t.asciz %s\n",
			name, strCount, value);
	strCount++;
	char *ret = (char *)malloc(sizeof(char)*strlen(buf)+1);
	strcpy(ret, buf);
	return ret;
}

char *getAsmChar(char *name, char *value) {
	while(value[0]=='\''||value[0]==' ') value++;
	while(value[strlen(value)-1]=='\'') value[strlen(value)-1] = '\0';
	static int cCount = 0;
	char nameBuf[strlen(name)+100];
	snprintf(nameBuf, sizeof(nameBuf), "wl_ch_%s%d", name, cCount);
	char buf[strlen(name)+strlen(value)+100];
	snprintf(buf, sizeof(buf),
			"\t.global %s\n%s:\n\t.byte %d\n",
			nameBuf, nameBuf, value[0]);
	cCount++;
	char *ret = (char *)malloc(sizeof(char)*strlen(buf)+1);
	strcpy(ret, buf);
	return ret;
}

char *getAsmInt(char *name, char *value) {
	/*TODO: make hex converter*/
	return " ";
}

char *getAsmFloat(char *name, char *value) {
	/*TODO: make hex converter*/
	return " ";
}

void convertVariables(AsmOut *out) {
	out->buffers.variables = (char *)malloc(sizeof(char));
	int totalSize = 1;
	int i;
	for(i=0;i<out->parser->totalVariables;i++) {		
		/* debugging
		 * printf("%s = %s\n", 
				out->parser->variables[i].varName,
				out->parser->variables[i].value);*/
		char *curName = out->parser->variables[i].varName;
		char *curValue = out->parser->variables[i].value;
		char *asmVar;	
		switch(out->parser->variables[i].type) {
			case INT: asmVar = getAsmInt(curName, curValue);break;
			case FLOAT: asmVar = getAsmFloat(curName, curValue);break;
			case STRING: asmVar = getAsmString(curName, curValue);break;
			case CHAR: asmVar = getAsmChar(curName, curValue);break;
		};
		if(asmVar!=NULL) {
			totalSize += strlen(asmVar);
			out->buffers.variables = (char *)realloc(
					out->buffers.variables, sizeof(char)*(totalSize+1));
			strcat(out->buffers.variables, asmVar);	
		}	
	}
}

/*
 * Run
 * */

void initHeader(AsmOut *out) {
	char *standardHead = 
		"\t.section __TEXT,__text\n\t.global _main\n\t.p2align 2\n";
	out->buffers.heading = (char *)malloc(sizeof(char)*strlen(standardHead)+10);
	strcpy(out->buffers.heading, standardHead);
}

void completeBuffer(AsmOut *out) {
	if(out->buffers.heading==NULL||
			out->buffers.variables==NULL) return;
	int totalSize = 
		strlen(out->buffers.heading)+
		strlen(out->buffers.variables);
	out->buffers.output.asmOutBuffer = (char *)malloc(sizeof(char)*(totalSize+100));
	strcpy(out->buffers.output.asmOutBuffer, out->buffers.heading);
	strcat(out->buffers.output.asmOutBuffer, out->buffers.variables);
}

void convertToAsm(AsmOut *out) {
	initHeader(out);
	convertVariables(out);

	completeBuffer(out);
	fprintf(out->asmOut, "%s", out->buffers.output.asmOutBuffer);
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


