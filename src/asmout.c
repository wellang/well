/*Copyright (c) 2024 Tristan Wellman*/

#include "asmout.h"
#include "hexconvert.h"
#include "cpu.h"

#include "ARM_MAC.h"

/*
 * Register conversion
 * */

/*
 * Instruction Conversion
 * */

char *convertInstructionAMD_X86_64(AsmOut *out, Instruction ins) {
	char outBuf[100];
	if(!strcmp(ins.instruction, "move")) {
		printf("%s\n", ins.arguments[0]);
		snprintf(outBuf, sizeof(outBuf), 
				"\tmov %s(%%rip),%s\n",
				ins.arguments[0], ins.arguments[1]);
	}
	char *ret = (char *)malloc(sizeof(char)*(strlen(outBuf)+2));
	strcpy(ret, outBuf);
	return ret;
} 

/* 
 * Funtion output
* */

char *getCPUMain() {
	char *ret = (char *)malloc(sizeof(char)*10);
	switch(CPU) {
		case ARM_MAC: strcpy(ret, "main"); break;
		case AMD_X86_64: strcpy(ret, "main"); break;
		case I386: strcpy(ret, "main"); break; 
		case ALPHA: break; /*TODO*/
		case ITANIUM_64: break; /*TODO*/
		case ARMv7: break; /*TODO*/
		case POWERPC: break; /*TODO*/
		case RS6000: break; /*TODO*/
		case SZ_IBM: break; /*TODO*/
		case SPARC: break; /*TODO*/
	}
	return ret;
}

char *createFunctionHeader(char *name) {
	if(!strcmp(name, "main")) name = getCPUMain();
	char head[strlen(name)+100];
	snprintf(head,sizeof(head),
			"\t.section __TEXT,__text\n\t.global _%s\n\t.p2align 2\n_%s:\n",
			name, name);
	char *ret = (char *)malloc(sizeof(char)*strlen(head)+2);
	strcat(ret, head);
	return ret;
}

void convertFunctions(AsmOut *out) {
	out->buffers.functions = (char *)malloc(sizeof(char));
	/*It actually makes me mad that I'm making sure memory is okay
	 * because of my schizo ass instruction issues. */
	*out->buffers.functions = '\0'; 
	size_t bufferSize=1;
	int i,j;
	for(i=0;i<out->parser->totalFunctions;i++) {
		char *header = createFunctionHeader(out->parser->functions[i].funName);
		bufferSize+=strlen(header)+1;
		out->buffers.functions =
			realloc(out->buffers.functions, bufferSize);
		strcat(out->buffers.functions, header);

		static int setAllocation = 0;
		/*instructions*/
		for(j=0;j<out->parser->functions[i].dataLength;j++) {
			Instruction *curIns = &out->parser->functions[i].instructions[j];
			if(curIns->instruction==NULL) continue;
			char *asmInstruction = NULL;
			char *stackAllocation = NULL;

			switch(CPU) {
				/*alpha*/
				case ALPHA: break; /*TODO*/
				/*intel*/
				case AMD_X86_64:							
							asmInstruction = convertInstructionAMD_X86_64(out, *curIns);
							break;
				case I386: break; /*TODO*/
				case ITANIUM_64: break; /*TODO*/
				/*ARM*/
				case ARM_MAC: 
							asmInstruction = convertInstructionARM_MAC(out, *curIns);
							stackAllocation = stackAllocateARM_MAC();
							break;
				case ARMv7: break; /*TODO*/
				/*IBM*/
				case POWERPC: break; /*TODO*/
				case RS6000: break; /*TODO*/
				case SZ_IBM: break; /*TODO*/
				/*SUN*/
				case SPARC: break; /*TODO*/
			};

			bufferSize+=strlen(asmInstruction)+
						strlen(stackAllocation)+2;
			out->buffers.functions =
				(char *)realloc(out->buffers.functions, bufferSize);
			if(setAllocation==0) {
				strcat(out->buffers.functions, stackAllocation);
				setAllocation=1;
			}
			strcat(out->buffers.functions, asmInstruction);
			free(asmInstruction);
		}
		setAllocation = 0;

		/*Check for void function type so we can return correctly*/
		if(out->parser->functions[i].type==VOID) {
			char *deallocateStack = NULL;
			switch(CPU) {
				case ALPHA: break; /*TODO*/
				case AMD_X86_64: break;
				case I386: break; /*TODO*/
				case ITANIUM_64: break; /*TODO*/
				case ARM_MAC: deallocateStack = stackDeallocateARM_MAC();break;
				case ARMv7: break; /*TODO*/
				case POWERPC: break; /*TODO*/
				case RS6000: break; /*TODO*/
				case SZ_IBM: break; /*TODO*/
				case SPARC: break; /*TODO*/
			};
			strcat(deallocateStack, "\tret\n");
			bufferSize+=strlen(deallocateStack)+2;
			out->buffers.functions =
				(char *)realloc(out->buffers.functions, bufferSize);
			strcat(out->buffers.functions, deallocateStack);
		}

	}
}

/* This should be pretty standard along all CPUs
 * Variable conversion
 * */

char *getAsmString(char *name, char *value) {
	static int strCount = 0;
	char buf[strlen(name)+strlen(value)+100];
	snprintf(buf, sizeof(buf),
			"wl_str.%s:\n\t.asciz %s\n",
			name, value);
	strCount++;
	char *ret = strdup(buf);
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
			"\n\t.global %s\n%s:\n\t.byte %d\n",
			nameBuf, nameBuf, value[0]);
	cCount++;
	char *ret = strdup(buf);
	return ret;
}

char *getAsmInt(char *name, char *value) {
	char *hexValue = uint64ToHex(value);
	static int iCount = 0;
	char nameBuf[strlen(name)+100];
	snprintf(nameBuf, sizeof(nameBuf), "wl_int_%s%d", name, iCount);
	char buf[strlen(nameBuf)+strlen(hexValue)+100];
	snprintf(buf, sizeof(buf), 
			"\n\t.global %s\n\t.p2align 2,0x0\n%s:\n\t.long %s\n",
			nameBuf, nameBuf, hexValue);	
	iCount++;
	char *ret = strdup(buf);
	return ret;
}

char *getAsmFloat(char *name, char *value) {
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
		char *curName = strdup(out->parser->variables[i].varName);
		char *curValue = strdup(out->parser->variables[i].value);
		char *asmVar;	
		switch(out->parser->variables[i].type) {
			case INT: asmVar = getAsmInt(curName, curValue);break;
			case FLOAT: asmVar = getAsmFloat(curName, curValue);break;
			case STRING: asmVar = getAsmString(curName, curValue);break;
			case CHAR: asmVar = getAsmChar(curName, curValue);break;
			case VOID: /*TODO*/break;
		};
		if(asmVar!=NULL) {
			totalSize += strlen(asmVar);
			out->buffers.variables = (char *)realloc(
					out->buffers.variables, sizeof(char)*(totalSize+2));
			strcat(out->buffers.variables, asmVar);	
		}	
	}
}

/*
 * Externals and inclusiom
 * */

void convertExternals_Includes(AsmOut *out) {
	out->buffers.externals = calloc(1, sizeof(char));
	int totalSize=1;
	int i;
	/*Externals*/
	for(i=0;i<out->parser->externals.externSize;i++) {
		char *curEx = strdup(out->parser->externals.externs[i]);
		char buf[strlen(curEx)+100];
		snprintf(buf, sizeof(buf), "\t.extern %s\n", curEx);
		if(curEx!=NULL) {
			totalSize+=strlen(buf);
			out->buffers.externals = 
				(char *)realloc(out->buffers.externals, sizeof(char)*(totalSize+2));
			strcat(out->buffers.externals, buf);
		}
	}
}

/*
 * Run
 * */

void completeBuffer(AsmOut *out) {
	if(out->buffers.functions==NULL||
			out->buffers.variables==NULL) return;
	int totalSize = 
		strlen(out->buffers.functions)+
		strlen(out->buffers.variables)+
		strlen(out->buffers.externals);
	out->buffers.output.asmOutBuffer = calloc(totalSize*100, sizeof(char));
	strcpy(out->buffers.output.asmOutBuffer, out->buffers.externals);
	strcat(out->buffers.output.asmOutBuffer, out->buffers.functions);
	strcat(out->buffers.output.asmOutBuffer, out->buffers.variables);
}

void convertToAsm(AsmOut *out) {
	convertExternals_Includes(out);
	convertFunctions(out);
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
	if(output==NULL) output = calloc(1, sizeof(AsmOut));
	output->parser = (struct parserData *)malloc(sizeof(*parser));
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

	output->buffers.output.AOBSize = 0;

	/*Don't forget output buffer is in parser->output.asmOutBuffer*/
}


