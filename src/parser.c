/*Copyright (c) 2024 Tristan Wellman*/
#include "parser.h"
#include "werror.h"

struct parserData *gPData;

/*
 * Checks if line contains important type:
 * EX: ~constants or ~type:function 
 * */
int checkImportantType(char *line) {
	int i, stype=0;
	for(i=0;line[i]!='\0';i++) {
		/* 
		 * ~ is the special sensor for types or instructions
		 * ~... is a spectial type,
		 * ...~ is a special instruction
		 * */
		if(line[i]=='~'&&(line[i+1]!='\0'&&line[i+1]!=' '))
			return 1;
	}
	return 0;
}

/* * * * *
 * Scope related functions!
 * * * * */
enum wTypes getScopeType(char *line) {
	if(strstr(line, "~constants")) return CONSTANTS;
	if(strstr(line, "~include")) return INCLUDE;
	int i, col=0, curl=0;
	for(i=0;line[i]!='\0';i++) {
		if(line[i]==':') col=1;
		if(line[i]=='{') curl=1;
	}
	if(curl&&!col) {
		if(strstr(line, "if")) return IFSTATE;
		if(strstr(line, "while")||
				strstr(line, "for")) return LOOP;
	}

	if(col&&curl) return FUNCTION;
	if(col&&!curl) return VARIABLE;

	return NONE;
}

char *getWT(enum wTypes t) {
	switch(t) {
		case NONE: return "NONE";
		case INCLUDE: return "INCLUDE";
		case FUNCTION: return "FUNCTION";
		case IFSTATE: return "IFSTATE";
		case LOOP: return "LOOP";
		case VARIABLE: return "VARIABLE";
		case CONSTANTS: return "CONSTANTS";
	}
}

char *getScopeName(char *line) {
	char tmp[1024];
	strcpy(tmp, line);
	char *aftrcurl = strstr(tmp, "~");
	if(aftrcurl!=NULL) {
		aftrcurl++;
		char *name;
		if((name = strstr(aftrcurl, ":"))&&name!=NULL) {
			name++;
			name = strtok(name, " ");
			if(name!=NULL) return name;
		} else if((name = strtok(aftrcurl, " {"))&&name!=NULL) return name;
	}

	return NULL;
}

void dumpScopes(struct parserData *parser) {
	int i;
	for(i=0;i<MAXSCOPES;i++) {
		if(parser->scopes[i].scopeName==NULL) break;
		char buffer[100];
		snprintf(buffer, sizeof(buffer), 
				"%s : %s : %s",
				getWT(parser->scopes[i].scopeType), 
				parser->scopes[i].scopeName,
				parser->fileBuffer[parser->scopes[i].lineNum]);
		WLOG(INFO, buffer);
	}
}

void getScopes(struct parserData *parser) {
	int i, j=0;

	for(i=0;i<parser->bufferSize;i++) {
		char *currentLine = parser->fileBuffer[i];
		if(currentLine!=NULL&&
				checkImportantType(currentLine)) {
			char *name = getScopeName(currentLine);
			Scope s = (Scope){ getScopeType(currentLine), NULL, i};
			s.scopeName = (char *)malloc(sizeof(char)*256);
			strcpy(s.scopeName, name);
			if(s.scopeType == NONE) continue;
			parser->scopes[j] = s;
			j++;
		}
	}
}

Scope getScopeAt(int lineNum, struct parserData *parser) {
	int i;
	for(i=0;i<MAXSCOPES&&parser->scopes[i].scopeName!=NULL;i++) {
		if(lineNum==parser->scopes[i].lineNum) return parser->scopes[i];
	}
	return (Scope){};
}

Scope getNextScope(Scope scope, struct parserData *parser) {
	int i;
	for(i=0;i<MAXSCOPES&&parser->scopes[i].scopeName!=NULL;i++) {
		if(scope.scopeName==parser->scopes[i].scopeName&&
				scope.lineNum==parser->scopes[i].lineNum) break;
	}
	for(i=i+1;i<MAXSCOPES&&parser->scopes[i].scopeName!=NULL;i++) {
		if(parser->scopes[i].scopeType!=IFSTATE&&
				parser->scopes[i].scopeType!=LOOP) return parser->scopes[i];
	}
	return (Scope){};
}

/* * * * *
 * Instruction related functions.
 * * * * */

void disectInstructionName(Instruction *ins) {
	if(ins->line!=NULL) {
		
	}
}

void parseInstruction(char *line, Instruction ins) {
	if(ins.line==NULL) ins.line = (char *)malloc(sizeof(char)*256);
	strcpy(ins.line, line);
	/*If you have an instruction name that is more than 50 characters... ._. */
	if(ins.instruction==NULL) ins.instruction = (char *)malloc(sizeof(char)*50);
	disectInstructionName(&ins);

		

}


/* * * * *
 * Function related functions
 * * * * */

void appendFuncArr(Function func, struct parserData *parser) {
	int i;
	for(i=0;i<MAXFUNCTIONS&&parser->functions[i].funName!=NULL;i++);
	parser->functions[i] = func;
}

int checkFuncForExternScope(int lineNum, struct parserData *parser) {
	int i;
	for(i=0;i<MAXSCOPES;i++) {
		if(parser->scopes[i].scopeName==NULL) break;
		if(parser->scopes[i].lineNum==lineNum&&
				(parser->scopes[i].scopeType==IFSTATE ||
				parser->scopes[i].scopeType==LOOP)) return 1;	
	}
	return 0;
}

int checkBrackFrom(int lineFrom, int lineTo, struct parserData *parser) {
	int i = lineFrom;
	for(;i<=lineTo;i++) {
		if(checkImportantType(parser->fileBuffer[i])) return 0;
		if(parser->fileBuffer[i][0]!='\n'&&
				strlen(parser->fileBuffer[i])!=1) return 1;
	}
	return 0;
}

/* Get all lines from a function scope into function buffer */
void buffToFunc(Function *func, struct parserData *parser) {
	/*NOTE: func data buffer must already be allocated, I aint checking it!*/
	int i = func->scope.lineNum+1;
	int scopeCarry=0; /*amount of scopes inside the function I.E. loops*/
	for(;i<parser->bufferSize;i++) {
		if(checkFuncForExternScope(i, parser)) scopeCarry++;
		if(strstr(parser->fileBuffer[i], "}")) {

			/*see if we are getting played*/
			if(scopeCarry==0) {
				if(!checkBrackFrom(i+1, 
					getNextScope(func->scope, parser).lineNum, parser)) {
					scopeCarry--;
					break;
				}
				scopeCarry--;
			}
			if(scopeCarry<0) break;
		}
		int pos = i-(func->scope.lineNum+1);
		func->data[pos] = (char *)malloc(sizeof(char)*1024);
		strcpy(func->data[pos], parser->fileBuffer[i]);
		func->dataLength++;
	}
	if(scopeCarry>0) {
		WLOG_WERROR(WERROR_MISSING_BRACKET, 
				parser->fData->fileName, 
				func->scope.lineNum,
				func->funName, "");
	}
}

void parseFunctionInstructions(Function *func) {
	int i;
	for(i=0;i<func->dataLength;i++) {
		if(checkImportantType(func->data[i])) continue;

		parseInstruction(func->data[i],
				func->instructions[i]);
	}
}

void getFunctionData(struct parserData *parser) {
	int i;
	/*scope ptr*/
	Scope *s = (Scope *)malloc(sizeof(Scope));
	for(i=0;i<MAXSCOPES&&parser->scopes[i].scopeName!=NULL&&
			(s=&parser->scopes[i]);i++) {
		/*Make sure it's a function scope*/
		if(s->scopeType==FUNCTION) {
			Function f;
			f.data = (char **)malloc(sizeof(char *)*DEFMAXFSIZE);
			f.dataLength = 0;
			f.funName = (char *)malloc(sizeof(char)*256);
			strcpy(f.funName, s->scopeName);
			f.scope = *s;

			buffToFunc(&f, parser);

			f.instructions = (Instruction *)malloc(sizeof(Instruction)*f.dataLength);
			parseFunctionInstructions(&f);

			appendFuncArr(f, parser);
		}
	}
}

void dumpFunctionData(struct parserData *parser) {
	int i,j;
	for(i=0;i<MAXFUNCTIONS&&parser->functions[i].funName!=NULL;i++) {
		WLOG(INFO, parser->functions[i].funName);
		for(j=0;j<parser->functions[i].dataLength;j++) {
			printf("%s", parser->functions[i].data[j]);
		}
	}
}

/* * * * *
 * Parser initialization and running functions
 * * * * */
void parseProgram(struct parserData *parser) {
	getScopes(parser);
	/* Useful for debugging
	* dumpScopes(parser);*/
	getFunctionData(parser);
	dumpFunctionData(parser);
	
}

struct parserData *initParser(wData *data) {
	gPData = (struct parserData *)malloc(sizeof(struct parserData));
	gPData->fData = data;

	WASSERT(gPData->fData->main!=NULL,
			"FATAL:: Main file not found!");


	gPData->fileBuffer = (char **)malloc(sizeof(char *)*1024);

	/*Get all the file data into the file buffer*/
	char line[1024];
	int i, mul=1;
	for(i=0;fgets(line, sizeof(line), gPData->fData->main)!=NULL;i++) { 
		if(i>=1024*mul) {
			gPData->fileBuffer = (char **)realloc(gPData->fileBuffer,
					sizeof(char *)*1024);
			mul++;
		} 

		gPData->fileBuffer[i] = (char*)malloc(sizeof(char)*ARRLEN(line));
		memcpy(gPData->fileBuffer[i], line, sizeof(line));
	}
	gPData->bufferSize = i;

	fclose(gPData->fData->main);

	return gPData;
}

void freeParser() {
	free(gPData->fileBuffer);
	/* TODO free all the other shit in functions,instructions,etc. */
}

