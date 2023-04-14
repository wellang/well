#include "util.h"
#include "convert.h"

struct {
    char *LINES[MAX_INT_S];
} line_data;

void convert_file_to_mfname(char *mfname_asm) {
    FILE *old = fopen("a.asm", "r");
    FILE *new = fopen(mfname_asm, "a");
    char line[256];
    int i = 0;
    while(fgets(line, sizeof(line), old) != NULL) {
        fprintf(new, "%s", line);
        i++;
    }

    fclose(old);
    fclose(new);

}