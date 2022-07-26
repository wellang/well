#include <stdio.h>
#include <string.h>

#include "libwesm/memory.h"
#include "log.h"

#include "asm2obj.h"

// Generate object code from asm
void asm2obj(char* asm_path, char* os, char* arch) {
    FILE* asm_file = fopen(asm_path, "r");

    char* obj_path = salloc(asm_path);
    obj_path = resalloc(obj_path, ".o");
    FILE* obj_file = fopen(asm_path, "wb");

    // Architecture of 32 bits
    if (strcmp(arch, "~x32") == 0) {

    // Illegal architecture
    } else {
        log_error("the specified architecture does not exist or is not supported '%s'", arch);
    }

    unsalloc(obj_path);
    fclose(asm_file); fclose(obj_file);
}

#define BYTE_TO_STR(_character_) ((char*)(char[]){(_character_), '\0'})

// Lexicographic analyzer (1 file of asm)
bool lexer(FILE* file, token_t* token, size_t* line_number, size_t* char_number) {
    char character; bool is_first = true;

    while ((character = (char)getc(file)) != (char)EOF) {
        switch (character) {

            // Skip whitespaces (and advance file-position)
            break; case ' ': case '\t': case '\r': (*char_number)++;   continue;
            break; case '\n': (*line_number)++;    (*char_number) = 0; continue;

            // Mnemonic token
            break; case 'a'...'z': case 'A'...'Z': case '_':
                unsalloc(token->value); (*char_number)++;

                token->id          =  TABLE__NAME;
                token->value       =  salloc(BYTE_TO_STR(character));
                token->line_number = *line_number;
                token->char_number = *char_number;

                while ((character = (char)getc(file)) != (char)EOF) {
                    switch (character) {

                        // Continuation of mnemonic
                        case 'a'...'z': case 'A'...'Z': case '_':
                            token->value = resalloc(token->value, BYTE_TO_STR(character));
                            continue;

                        // End of mnemonic
                        default: ungetc(character, file); return true;
                    }
                }
                return true;

            // Mnemonic token
            break; case '0'...'9':
                unsalloc(token->value); (*char_number)++;

                token->id          =  TABLE__NUMBER;
                token->value       =  salloc(BYTE_TO_STR(character));
                token->line_number = *line_number;
                token->char_number = *char_number;

                while ((character = (char)getc(file)) != (char)EOF) {
                    switch (character) {

                        // Continuation of number
                        case '0'...'9':
                            token->value = resalloc(token->value, BYTE_TO_STR(character));
                            continue;

                        // End of number
                        default: ungetc(character, file); return true;
                    }
                }
                return true;

            // String ("..")
            break; case '"':
                unsalloc(token->value); (*char_number)++;

                token->id          =  TABLE__STRING_DOUBLE_QUOTES;
                token->line_number = *line_number;
                token->char_number = *char_number;

                is_first = true;
                while ((character = (char)getc(file)) != (char)EOF) {
                    switch (character) {

                        // End of string
                        case '"': return true;

                        // Content of string
                        default:
                            if (is_first) {
                                token->value = salloc(BYTE_TO_STR(character));
                                is_first = false;
                                continue;
                            }

                            token->value = resalloc(token->value, BYTE_TO_STR(character));
                            continue;
                    }
                }
                return true;

            // String ("..")
            break; case '\'':
                unsalloc(token->value); (*char_number)++;

                token->id          =  TABLE__STRING_SINGLE_QUOTES;
                token->line_number = *line_number;
                token->char_number = *char_number;

                is_first = true;
                while ((character = (char)getc(file)) != (char)EOF) {
                    switch (character) {

                        // End of string
                        case '\'': return true;

                        // Content of string
                        default:
                            if (is_first) {
                                token->value = salloc(BYTE_TO_STR(character));
                                is_first = false;
                                continue;
                            }

                            token->value = resalloc(token->value, BYTE_TO_STR(character));
                            continue;
                    }
                }
                return true;

            // Illegal token
            break; default:
                unsalloc(token->value); (*char_number)++;

                token->id          =  TABLE__NAME;
                token->value       =  salloc(BYTE_TO_STR(character));
                token->line_number = *line_number;
                token->char_number = *char_number;
                return true;
        }
    }

    return false;
}

// Syntactic analyzer (1 file of asm)
void parser(char* asm_path, char* codegen) {
    FILE* asm_file = fopen(asm_path, "r");
    size_t line_number = 1; size_t char_number = 0;

    // Error of opening of file
    if (asm_file == NULL) {
        log_error("the file could not be opened '%s'", asm_path);
    }

    token_t token = {
        id:          TABLE__ILLEGAL,
        value:       NULL,
        line_number: 1,
        char_number: 0
    };

    while (lexer(asm_file, &token, &line_number, &char_number)) {
        printf("[%s]", token.value);
    }

    free(token.value); // Remove last token (analyzed)
    fclose(asm_file);
}

// Remove macros (locals)
#undef BYTE_TO_STR
