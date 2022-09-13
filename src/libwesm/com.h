#include <stdbool.h>
#include "../log.h"

#ifndef COM_H_
#define COM_H_

typedef struct {

    bool IS_THERE;
    char *C;
    char *ASM;

    const char *fname;
    int line_num;


} COM;

#define log_com(line, line_num, IS_COM, ...)    \
    COM com; \
    __log_log__(3, com->fname, com->line_num, (const char *)line)

bool __check_com__(char line[]);

#endif // COM_H_
