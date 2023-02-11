/*Copyright (c) 2022 TristanWellman*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "log.h"
#include "operators.h"
#include "asm_loops.h"

struct loop_data LDATS;

int while_interp(FILE *out, char line[], int line_num, int whilenum_ln,
              const char *fname, const char *funcname, int whilenum, bool is_in_if) {

    out = fopen("a.asm", "a");

    char *op = check_operator(line, funcname, whilenum_ln, whilenum);
    if (op != NULL) {
        char *noop = strstr(op, "NO_OP");
        if (noop != NULL) { return 0; }

        fprintf(out, "%s", op);
    }
}


/*
 * For loops in wellang expect you to have declared what is in the first argument prior to the for loop.
 * ---- ---- ----
 * ex:
 * move~ 1, rdi
 * move~ 2, rsi
 * ~for(rdi < rsi:add~ rdi, 1)
 * ---- ---- ----
 * rdi & rsi are given values prior to the for loop unlike c where is declared in the for loop :: for(i = 0; i < j; i++)
 * */
int for_interp(FILE *out, char line[], int line_num, int fornum_ln,
              const char *fname, const char *funcname, int fornum, bool is_in_if) {

    out = fopen("a.asm", "a");

    char *for_ = strstr(line, "~for");
    if(for_ != NULL) {
        char *find_instruc = strstr(line, ":");
        if (find_instruc != NULL) {
            const char delim[] = ")";
            /*should be something like "add~ r8, 1"*/
            char *instruction = strtok(find_instruc, delim);
            LDATS.INS_FOR_LAT = instruction;

            char *op = check_operator(line, funcname, fornum_ln, fornum);
            if (op != NULL) {
                /*char *noop = strstr(op, "NO_OP");
                if (noop != NULL) { return 0; }*/
                fprintf(out, "%s", op);
            }
        } else {
            wlog_error(fname, line_num, "For loop missing instruction! ex: ~for(r8 < r9:add~ 1, r8) {}\n"
                                        "       |\n"
                                        "   %d|\t%s\n", line_num, line);

            return 1;
        }
    }
}


