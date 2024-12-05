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
	if(strstr(line, "~extern")) return EXTERN;
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
		case EXTERN: return "EXTERN";
	}
	return "";
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


/*
 * Variable related functions
 * */

void dumpVariables(struct parserData *parser) {
	int i;
	for(i=0;i<parser->totalVariables;i++) {
		printf("%s:%s\n", parser->variables[i].varName,
				parser->variables[i].value);
	}
}

void setVariableType(Variable *var, char *type,
		int lineNum, char *file) {
	if(!strcmp(type, "string")) {
		var->type = STRING; return;
	} else if(!strcmp(type, "char")) {
		var->type = CHAR; return;
	} else if(!strcmp(type, "int")) {
		var->type = INT; return;
	} else if(!strcmp(type, "float")) {
		var->type = FLOAT; return;
	} else if(!strcmp(type, "void")) {
		var->type = VOID; return;
	}
	WLOG_WERROR(WERROR_UNDEFINED_TYPE,
			file, lineNum, "constants", "");
}

Variable getVarFrom(struct parserData *parser, char *name) {
	int i;
	for(i=0;i<parser->totalVariables;i++) {
		if(!strcmp(parser->variables[i].varName, name)) return parser->variables[i];
	}
	return (Variable){};
}

/*This is expected to be ran AFTER scopes have been initialized*/
void getVariables(struct parserData *parser) {

	/*default to 1 and realloc for each one so it's more dynamic
	 * I know it's slower...*/
	parser->variables = (Variable *)malloc(sizeof(Variable));
	parser->totalVariables = 0;

	int i, j=0;
	for(i=0;i<MAXSCOPES;i++) {
		if(parser->scopes[i].scopeName==NULL) break;
		
		if(parser->scopes[i].scopeType == VARIABLE) {
			
			parser->variables = (Variable *)realloc(parser->variables, 
					sizeof(Variable)*(parser->totalVariables+1));
			char *line = parser->fileBuffer[parser->scopes[i].lineNum];
			char *data = strstr(line, "=");
			if(data==NULL) {
 				WLOG_WERROR(WERROR_UNINITIALIZED_VARIABLE,
						parser->fData->fileName, 
						parser->scopes[i].lineNum, "constants", "");	
			} else {
				data++;
				if(data[strlen(data)-1]=='\n') data[strlen(data)-1] = '\0';
				while(data[0]==' ') data++;
				parser->variables[j].value = (char *)malloc(sizeof(char)*strlen(data));
				strcpy(parser->variables[j].value, data);
				/*save data*/
				/*EATTABS(line);*/
				char *tmp  = (char *)malloc(sizeof(char)*strlen(line));
				strcpy(tmp, line);
				
				/*type*/
				char *type = strstr(line, "~");
				/*we don't need to check cuz it was already processed*/
				type++;
				type = strtok(type, ":");
				setVariableType(&parser->variables[j], type,
						parser->scopes[i].lineNum, parser->fData->fileName);

				/*name, once again we don't need to check*/
				char *name = strstr(tmp, ":");
				name++;
				
				name = strtok(name, "=");
				while(name[strlen(name)-1]==' ') name[strlen(name)-1] = '\0';
				parser->variables[j].varName = (char *)malloc(sizeof(char)*strlen(name));
				parser->variables[j].varName = strdup(name);
				parser->totalVariables++;
				j = parser->totalVariables;
				free(tmp);
			}
		}
	}
}

/* * * * *
 * Instruction related functions.
 * * * * */

/*copy the whole structure.
 * I have been trying to figure out this stupid 
 * missing instruction argument with the second instruction(specifically) issue.
 *
 * Maybe this will help me fix it. Idk, I've been up figuring this out for 10 hours.
 * Update: It didn't fix anything and is now useless :) */
Instruction instructionDup(const Instruction *src) {
	Instruction ret;
	memset(&ret, 0, sizeof(Instruction));

	ret.argLen = src->argLen;
	ret.capacity = src->capacity;
	if(src->line!=NULL) ret.line = strdup(src->line);
	if(src->instruction!=NULL) ret.instruction = strdup(src->instruction);

	if(src->argLen>0&&src->arguments!=NULL) {
		ret.arguments = calloc(src->capacity>0 ? src->capacity : DEFAULTINSARGSIZE, 
				sizeof(char *));
		int i;
		for(i=0;i<src->argLen;i++) {
			if(src->arguments[i]!=NULL) 
				ret.arguments[i] = strdup(src->arguments[i]);
		}
	}
	return ret;
}

void appendInsArgs(Instruction *ins, char *arg) {
	while(arg[0]==' ') arg++;
	if(ins->argLen>=ins->capacity) {
        size_t newCapacity = ins->capacity==0 ? DEFAULTINSARGSIZE : ins->capacity*2;
        char **newArgs = realloc(ins->arguments, sizeof(char *)*newCapacity);
        ins->arguments = newArgs;
    	ins->capacity = newCapacity;
	} 
	ins->arguments[ins->argLen] = strdup(arg);
	ins->argLen++;

}

void getInstructionArguments(Instruction *ins) {
	if(ins->line!=NULL) {
		ins->argLen = 0;
		ins->capacity = DEFAULTINSARGSIZE;
		ins->arguments = calloc(ins->capacity, sizeof(char *));
		char *backup = strdup(ins->line);
		char *ignoreIns = strstr(backup, "~");
		if(ignoreIns!=NULL) {
			ignoreIns++;
			char *arg = strtok(ignoreIns, ",");
			while(arg!=NULL) {
				int i;
				for(i=0;i<strlen(arg);i++) {
					if(arg[i]=='\n') arg[i] = '\0';
				}
				appendInsArgs(ins, arg);
				arg = strtok(NULL, ",");
			}
		}
		free(backup);
	}
	if(ins->argLen==0) ins->arguments = NULL;
}

void disectInstructionName(Instruction *ins) {
	if(ins->line!=NULL) {
		char *backup = strdup(ins->line);
		EATTABS(backup);
		/*move~ text, r1*/
		char *name = strtok(backup, "~");
		if(name!=NULL) ins->instruction = strdup(name);
		free(backup);
	}
}

void parseInstruction(char *line, Instruction *ins) {
    if (ins==NULL||line==NULL) return;
	memset(ins, 0, sizeof(Instruction));
	ins->line = NULL;
    ins->instruction = NULL;
    ins->arguments = NULL;
    ins->line = strdup(line);
    /*If you have an instruction name that is more than 50 characters... ._. */
    ins->instruction = calloc(50, sizeof(char));
	
	disectInstructionName(ins);
	getInstructionArguments(ins);
}


/* * * * *
 * Function related functions
 * * * * */


void appendFuncArr(Function func, struct parserData *parser) {
	int i;
	for(i=0;i<MAXFUNCTIONS&&parser->functions[i].funName!=NULL;i++);
	parser->functions[i] = func;
	parser->totalFunctions++;
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
		func->data[pos] = strdup(parser->fileBuffer[i]);
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
	int i,j=0;
	for(i=0;i<func->dataLength;i++,j++) {
		if(func->data[i]==NULL||
				strlen(func->data[i])<=1||
				checkImportantType(func->data[i])) {
			if(j>0) j--;
			continue;
		}
		parseInstruction(func->data[i],
				&func->instructions[j]);
	}
}

void getFunctionType(struct parserData *parser, Function *func) {
	char *line = strdup(
			parser->fileBuffer[func->scope.lineNum]);
	char *type = strstr(line, "~");
	if(type!=NULL) {
		type++;
		type = strtok(type, ":");
		Variable grabtype;
		setVariableType(&grabtype, type,
				func->scope.lineNum, parser->fData->fileName);
		func->type = grabtype.type;
	}
}

int verifyFunctionReturn(struct parserData *parser, Function *func) {
	
	int i;
	if(func->type==VOID) return 1; /*you don't need to return in void*/
	for(i=0;i<func->dataLength&&
			func->instructions[i].instruction!=NULL;i++) {
		if(!strcmp(func->instructions[i].instruction, "return")) {
			return 1;
		}
	}

	WLOG_WERROR(WERROR_NO_RETURN, 
			parser->fData->fileName, func->scope.lineNum, 
			func->funName, "");
	return 0;
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
			memset(&f, 0, sizeof(Function));
			f.data = calloc(DEFMAXFSIZE, sizeof(char *));
			f.dataLength = 0;
			f.funName = calloc(256, sizeof(char));
			f.funName = strdup(s->scopeName);
			f.scope = *s;

			buffToFunc(&f, parser);
			getFunctionType(parser, &f);

			f.instructions = calloc(f.dataLength+10, sizeof(Instruction));
			parseFunctionInstructions(&f);

			if(verifyFunctionReturn(parser, &f)) appendFuncArr(f, parser);
		}
	}
}

void dumpFunctionData(struct parserData *parser) {
	int i,j;
	for(i=0;i<MAXFUNCTIONS&&parser->functions[i].funName!=NULL;i++) {
		WLOG(INFO, parser->functions[i].funName);
		for(j=0;j<parser->functions[i].dataLength;j++) {
			printf("%s", parser->functions[i].data[j]);
			printf("%s\n", parser->functions[i].instructions[j].arguments[0]);
		}
	}
}

int verifyMainFunction(struct parserData *parser) {
	int i;
	for(i=0;i<MAXFUNCTIONS&&parser->functions[i].funName!=NULL;i++) {
		if(!strcmp(parser->functions[i].funName, "main")) return 1;
	}
	WLOG_WERROR(WERROR_MAIN, 
				parser->fData->fileName, 
				0, "Global", "");
	return 0;
}


/*
 * Compiler directive handling
 * */
void getCompTimeDirectives(struct parserData *parser) {
	parser->compDirectives.NOMAIN = 0;
	int i;
	for(i=0;i<parser->bufferSize;i++) {
		char *line = strdup(parser->fileBuffer[i]);
		char *directive = strchr(line, '#');
		if(directive!=NULL) {
			directive++;
			while(directive[strlen(directive)-1]=='\n') directive[strlen(directive)-1] = '\0';
			directive = strtok(directive, " ");
			/*See what the directive is*/
			if(!strcmp(directive, "nomain")||
					!strcmp(directive, "NOMAIN")) parser->compDirectives.NOMAIN=1;
		}
	}
}


/*
 * Extern handling
 * */

void getExternals(struct parserData *parser) {
	static int defaultArrSize = 100;
	parser->externals.externs = calloc(defaultArrSize+2, sizeof(char *));
	parser->externals.capacity = defaultArrSize;
	parser->externals.externSize = 0;
	int i;
	for(i=0;i<MAXSCOPES&&parser->scopes[i].scopeName!=NULL;i++) {
		if(parser->scopes[i].scopeType==EXTERN) {
			char *line = strdup(parser->fileBuffer[parser->scopes[i].lineNum]);
			char *external = strstr(line, "~extern");
			if(external!=NULL) {
				external+=strlen("~extern");
				while(external[0]==' ') external++;
				while(external[strlen(external)-1]=='\n') external[strlen(external)-1] = '\0';
				if(parser->externals.externSize>=parser->externals.capacity) {
					parser->externals.capacity*=2;
					parser->externals.externs = 
						(char **)realloc(parser->externals.externs, 
								sizeof(char *)*parser->externals.capacity);
				}
				parser->externals.externs[parser->externals.externSize] =
					strdup(external);
				parser->externals.externSize++;
			} else {
				WLOG_WERROR(WERROR_EXTERN_NOVALUE,
						parser->fData->fileName, 
						parser->scopes[i].lineNum, "Global", "");	
			}
		}
	}
}

/* TODO
 * Inclusion handling
 * */

/* * * * *
 * Parser initialization and running functions
 * * * * */



void parseProgram(struct parserData *parser) {
	getCompTimeDirectives(parser);

	getScopes(parser);
	getExternals(parser);
	getFunctionData(parser);
	getVariables(parser);
	if(!parser->compDirectives.NOMAIN)
		verifyMainFunction(parser);
	/*dumpVariables(parser);*/
	/* Useful for debugging*/
	 /*dumpScopes(parser);*/
	 /*dumpFunctionData(parser);*/
	
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

	gPData->totalFunctions = 0;

	return gPData;
}

void freeParser(struct parserData *parser) {
	int i,j,k;
	if(parser == NULL) return;
    /*fileBuffer*/
    if(parser->fileBuffer) {
        for (i = 0; i < parser->bufferSize; i++) {
            free(parser->fileBuffer[i]);
        }
        free(parser->fileBuffer);
    }
    /*Functions*/
    for(i = 0;i<MAXFUNCTIONS&&parser->functions[i].funName != NULL;i++) {
        Function *func = &parser->functions[i];
        free(func->funName);
        if(func->data) {
            for(j = 0;j<func->dataLength;j++) free(func->data[j]);
            free(func->data);
        }
        /*instructions*/
        if(func->instructions) {
            for(j = 0;j<func->dataLength;j++) {
                Instruction *ins = &func->instructions[j];
                free(ins->line);
                free(ins->instruction);
                if(ins->arguments) {
                    for(k = 0;k<ins->argLen;k++) free(ins->arguments[k]);
                    free(ins->arguments);
                }
            }
            free(func->instructions);
        }
    }
    /*variables*/
    if(parser->variables) {
        for (i = 0;i<parser->totalVariables;i++) {
            free(parser->variables[i].varName);
            free(parser->variables[i].value);
        }
        free(parser->variables);
    }
    /*scopes*/
    for(i = 0;i<MAXSCOPES&&parser->scopes[i].scopeName != NULL;i++)
        free(parser->scopes[i].scopeName);

    free(parser);
}

