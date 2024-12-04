/*Copyright (c) 2024 Tristan Wellman*/
#ifndef PARSER_H
#define PARSER_H

#include <carray.h>
#include "util.h"
#include "wdata.h"
#include "werror.h"

#define STRING_ARRAY_TYPE                   char*
#define STRING_ARRAY_HEAP                   1
#define STRING_ARRAY_FREE(value)            NULL
#define STRING_ARRAY_COMPARE(cmp_a, cmp_b)  (strcmp(cmp_a, cmp_b) == 0)

struct StringArray {
    int length;
    int capacity;
    char **contents;
};

enum wTypes {
	NONE=0,
	INCLUDE,
	EXTERN,
	FUNCTION,
	IFSTATE,
	LOOP,
	VARIABLE,
	CONSTANTS /*This one is specific to wellang design*/
};


enum varTypes {
	INT,
	CHAR,
	STRING,
	FLOAT,
	VOID,
};

/*
 * If you need more than that many scopes in a file,
 * you should re-think what you are doing
 * */
#define MAXSCOPES 100000

#define MAXFUNCTIONS 10000
#define DEFMAXFSIZE 100000 /*default max amount of lines for a function*/

#define DEFAULTINSARGSIZE 2

/*Declarations for dynamic scope arrays*/
typedef struct {
	enum wTypes scopeType;
	char *scopeName;
	int lineNum;
} Scope;

typedef struct {
	char *line; /* move~ 1, r */
	char *instruction; /* move */
	char **arguments; /* ["1", "r1"] */
	int argLen;
	int capacity;
} Instruction;

typedef struct {
	enum varTypes type;
	char *funName;
	char **data; /*All the code inside the function scope*/
	int dataLength;
	Scope scope;
	/*needs malloced to amount of lines in function*/
	Instruction *instructions;
} Function;

typedef struct {
	enum varTypes type;
	char *varName;
	char *value;
} Variable;

/*Struct to hold arrays of parser handy data*/
struct parserData {
	wData *fData;
	
	char **fileBuffer;
	int bufferSize;

	Scope scopes[MAXSCOPES];
	Function functions[MAXFUNCTIONS];
	int totalFunctions;
	Variable *variables;
	int totalVariables;
};

/**
 * Function Prototypes
 * */
Variable getVarFrom(struct parserData *parser, char *name);
Instruction instructionDup(const Instruction *src);

void parseProgram(struct parserData *parser);
struct parserData *initParser(wData *data);
void freeParser(struct parserData *parser);

#endif
