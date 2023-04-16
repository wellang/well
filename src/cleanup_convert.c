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
    while(fgets(line, sizeof(line), old) != NULL) {
        fprintf(new, "%s", line);/*temporary until cleanup*/
        i++;
    }

    cleanup(mfname_asm);

    fclose(old);
    fclose(new);

}