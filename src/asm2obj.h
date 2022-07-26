#pragma once

// Generate object code from asm
void asm2obj(char*, char*, char*);

// Table of tokens
enum {
    TABLE__NAME,                 // mov, add, sub, var_name, ..
    TABLE__NUMBER,               // 100
    TABLE__STRING_DOUBLE_QUOTES, // "Hi!"
    TABLE__STRING_SINGLE_QUOTES, // 'Hi!'
    TABLE__ILLEGAL
};

// Items of file
typedef struct {
    unsigned char id;
    char*         value;
    size_t        line_number;
    size_t        char_number;
} token_t;

// Lexicographic analyzer (1 file of asm)
bool lexer(FILE* file, token_t* token, size_t* line_number, size_t* char_number);

// Syntactic analyzer (1 file of asm)
void parser(char* asm_path, char* codegen);
