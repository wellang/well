#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "if.h"

#include "log.h"
#include "libwesm/com.h"

#include "asm_interp_funcs.h"

#define if_error "if statement error! EX: ~if(x == y) start\n"

int if_interp(FILE *out, char line[], int line_num, const char *fname, const char *funcname, int ifnum) {

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

                const char delim[] = "==";
                char *op2 = strstr(in_bracs, "==");
                if(op2 != NULL) {op2++;op2++;op2++;}
                char *op1 = strtok(in_bracs, delim);
                op1[strlen(op1)-1] = '\0';
                char opb[0x100];
                snprintf(opb, sizeof(opb), "%s,%s", op1, op2);
                char buf[0x100];
                snprintf(buf, sizeof(buf), "\n\tcmp %s, %s\n\tje %s._%d%s%s_eq\n\tjne %s._%d_fin\n\t._%d%s%s_eq:",
                         op1, op2,
                         funcname, ifnum, op1, op2,
                         funcname, ifnum,
                         ifnum, op1, op2);
                fprintf(out, buf);

                //asm_interp_func_funcs(line, out, line_num, fname, funcname);
             } else if (eq_ == NULL &&
                        neq_ != NULL &&
                        gre_ == NULL &&
                        les_ == NULL &&
                        gre_or_eq_ == NULL &&
                        les_or_eq_ == NULL) {

                const char delim[] = "!=";
                char *op2 = strstr(in_bracs, "!=");
                if(op2 != NULL) {op2++;op2++;op2++;}
                char *op1 = strtok(in_bracs, delim);
                op1[strlen(op1)-1] = '\0';
                char buf[0x100];
                snprintf(buf, sizeof(buf), "\n\tcmp %s, %s\n\tjne %s._%d%s%s_neq\n\tje %s._%d_fin\n\t._%d%s%s_neq:",
                         op1, op2,
                         funcname, ifnum, op1, op2,
                         funcname, ifnum,
                         ifnum, op1, op2);
                fprintf(out, buf);

            } else if(eq_ == NULL &&
                      neq_ == NULL &&
                      gre_ != NULL &&
                      les_ == NULL &&
                      gre_or_eq_ == NULL &&
                      les_or_eq_ == NULL) {

                const char delim[] = ">";
                char *op2 = strstr(in_bracs, ">");
                if(op2 != NULL) {op2++;op2++;} else {
                    wlog_error(fname, line_num, if_error);
                }
                char *op1 = strtok(in_bracs, delim);
                if (op1 == NULL) {wlog_error(fname, line_num, if_error);}
                op1[strlen(op1)-1] = '\0';
                char buf[0x100];
                snprintf(buf, sizeof(buf), "\n\tcmp %s, %s\n\tjg %s._%d%s%s_gre\n\tjng %s._%d_fin\n\t._%d%s%s_gre:",
                         op1, op2,
                         funcname, ifnum, op1, op2,
                         funcname, ifnum,
                         ifnum, op1, op2);
                fprintf(out, buf);
            } else if(eq_ == NULL &&
                      neq_ == NULL &&
                      gre_ == NULL &&
                      les_ != NULL &&
                      gre_or_eq_ == NULL &&
                      les_or_eq_ == NULL) {

                const char delim[] = "<";
                char *op2 = strstr(in_bracs, "<");
                if(op2 != NULL) {op2++;op2++;} else {
                    wlog_error(fname, line_num, if_error);
                }
                char *op1 = strtok(in_bracs, delim);
                if(op1 == NULL) {wlog_error(fname, line_num, if_error);}
                op1[strlen(op1)-1] = '\0';
                char buf[0x100];
                snprintf(buf, sizeof(buf), "\n\tcmp %s, %s\n\tjl %s._%d%s%s_les\n\tjnl %s._%d_fin\n\t._%d%s%s_les:",
                         op1, op2,
                         funcname, ifnum, op1, op2,
                         funcname, ifnum,
                         ifnum, op1, op2);
                fprintf(out, buf);
            }
        }
    }
    fclose(out);
    return 0;
}

int if_end_interp(FILE *out, char line[], int line_num, const char *fname, const char *funcname, int ifnum) {

    char *end = strstr(line, "end");
    out = fopen("a.asm", "a");
    if(end != NULL) {

        wlog_info(fname, line_num, "Found 'END' in if statement\n");

        char buff[0x100];
        snprintf(buff, sizeof(buff), "\n\tjmp %s._%d_fin\n\t._%d_fin:",
        funcname, ifnum,
        ifnum);
        fprintf(out, buff);
        fclose(out);
    }
    return 0;
}
