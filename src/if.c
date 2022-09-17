#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "if.h"

#include "log.h"
#include "libwesm/com.h"

#include "asm_interp_funcs.h"

char *opp2;
char *opp1;
int randd;

#define if_error "if statement error! EX: ~if(x == y) start\n"

int if_interp(FILE *out, char line[], int line_num, const char *fname, const char *funcname) {

    out = fopen("a.asm", "a");

    char if_[] = "~if";
    char *search_if = strstr(line, if_);
    if(search_if != NULL) {

        const char delim[] = ")";
        //const char delim2[] = "}";
        char *first = strchr(line, '(');
        char *start = strstr(line, "start");
        //char *sec = strchr(line, '{');

        if(first != NULL) {
            first++;
        }
        char *in_bracs = strtok(first, delim);

        //log_info(in_bracs);

        if(in_bracs != NULL) {

            srand(time(NULL));
            int r = rand() % 9999;
            randd = r;
            char eq[] = "==";
            char neq[] = "!=";
            char gre[] = ">";
            char les[] = "<";
            char gre_or_eq[] = ">=";
            char les_or_eq[] = "<=";

            char *eq_ = strstr(in_bracs, eq);
            char *neq_ = strstr(in_bracs, neq);
            char *gre_ = strstr(in_bracs, gre);
            char *les_ = strstr(in_bracs, les);
            char *gre_or_eq_ = strstr(in_bracs, gre_or_eq);
            char *les_or_eq_ = strstr(in_bracs, les_or_eq);
            if(eq_ != NULL &&
               neq_ == NULL &&
               gre_ == NULL &&
               les_ == NULL &&
               gre_or_eq_ == NULL &&
               les_or_eq_ == NULL
            ) {
                int rando = r;
                const char delim[] = "==";
                char *op2 = strstr(in_bracs, "==");
                if(op2 != NULL) {op2++;op2++;op2++;}
                char *op1 = strtok(in_bracs, delim);
                op1[strlen(op1)-1] = '\0';
                char opb[0x100];
                snprintf(opb, sizeof(opb), "%s,%s", op1, op2);
                char buf[0x100];
                snprintf(buf, sizeof(buf), "\n\tcmp %s, %s\n\tje %s.%d%s%seq\n\tjne %s.%dfin\n\t.%d%s%seq:",
                         op1, op2,
                         funcname, rando, op1, op2,
                         funcname, rando,
                         rando, op1, op2);
                fprintf(out, buf);

                //asm_interp_func_funcs(line, out, line_num, fname, funcname);
             } else if (eq_ == NULL &&
                        neq_ != NULL &&
                        gre_ == NULL &&
                        les_ == NULL &&
                        gre_or_eq_ == NULL &&
                        les_or_eq_ == NULL) {

                int rando = r;
                const char delim[] = "!=";
                char *op2 = strstr(in_bracs, "!=");
                if(op2 != NULL) {op2++;op2++;op2++;}
                char *op1 = strtok(in_bracs, delim);
                op1[strlen(op1)-1] = '\0';
                char buf[0x100];
                snprintf(buf, sizeof(buf), "\n\tcmp %s, %s\n\tjne %s.%d%s%sneq\n\tje %s.%dfin\n\t.%d%s%sneq",
                         op1, op2,
                         funcname, rando, op1, op2,
                         funcname, rando,
                         rando, op1, op2);
                fprintf(out, buf);

            }
        }
    }
    fclose(out);
    return 0;
}

int if_end_interp(FILE *out, char line[], int line_num, const char *fname, const char *funcname) {

    char *end = strstr(line, "end");
    out = fopen("a.asm", "a");
    if(end != NULL) {

        wlog_info(fname, line_num, "Found 'END' in if statement\n");

        char buff[0x100];
        snprintf(buff, sizeof(buff), "\n\tjmp %s.%dfin\n\t.%dfin:",
        funcname, randd,
        randd);
        fprintf(out, buff);
        fclose(out);
    }
    return 0;
}
