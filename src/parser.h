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
	FUNCTION,
	IFSTATE,
	LOOP,
	VARIABLE,
	CONSTANTS /*This one is specific to wellang design*/
};


/*
 * If you need more than that many scopes in a file,
 * you should re-think what you are doing
 * */
#define MAXSCOPES 100000

#define MAXFUNCTIONS 10000
#define DEFMAXFSIZE 100000 /*default max amount of lines for a function*/

/*Declarations for dynamic scope arrays*/
typedef struct {
	enum wTypes scopeType;
	char *scopeName;
	int lineNum;
} Scope;

typedef struct {
	char *line; /* move~ 1, r */
	char *instruction; /* move */
	char **arguments; /* ["1", "r"] */
} Instruction;

typedef struct {
	char *funName;
	char **data; /*All the code inside the function scope*/
	int dataLength;
	Scope scope;
	/*needs malloced to amount of lines in function*/
	Instruction *instructions;
} Function;

struct parserOut {
	char **asmOutBuffer;
	int AOBSize;

};

/*Struct to hold arrays of parser handy data*/
struct parserData {
	wData *fData;
	
	char **fileBuffer;
	int bufferSize;

	struct parserOut output;

	Scope scopes[MAXSCOPES];
	Function functions[MAXFUNCTIONS];
};

/**
 * Function Prototypes
 * */
void parseProgram(struct parserData *parser);
struct parserData *initParser(wData *data);

#endif
