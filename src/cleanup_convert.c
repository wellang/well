#include "util.h"
#include "cleanup_convert.h"

void cleanup(char *mfname_asm) {
    /*TODO: cleanup asm file*/

}

void convert_file_to_mfname(char *mfname_asm) {
    FILE *old = fopen("a.asm", "r");
    FILE *new = fopen(mfname_asm, "a");
    char line[256];
    int i = 0;

    welldb_create_table("A_ASM_FDATA", "LINE CHAR(256)");

    while(fgets(line, sizeof(line), old) != NULL) {
        if(!strcmp(line, "\n")) {
            continue;
        }
        char buf[0x100];
        snprintf(buf, sizeof(buf), "\"%s\"", line);
        welldb_add_data("A_ASM_FDATA (LINE)", buf);
        fprintf(new, "%s", line); /*temporary until cleanup*/
        i++;
    }

    cleanup(mfname_asm);
    welldb_drop_table("A_ASM_FDATA");

    fclose(old);
    fclose(new);

}