#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "com.h"

bool __check_com__(char line[]) {

    bool IS_COM;

    COM com;

    char com_c[] = "// ";
    char com_wesm[] = "; ";

    com.C = strstr(line, com_c);
    com.ASM = strstr(line, com_wesm);

    if(com.C != NULL || com.ASM != NULL) {
        com.IS_THERE = true;
    } else if (com.C == NULL && com.ASM == NULL) {
        com.IS_THERE = false;
    }

    IS_COM = com.IS_THERE;

    return IS_COM;
}
