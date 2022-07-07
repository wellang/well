#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int syscall_interp(char line[], FILE *out) {

	char search[] = "syscall";

	char *syscall = strstr(line, search);

	if(syscall != NULL) {
	
		out = fopen("a.asm", "a");

		fprintf(out, "; %s\n\tsyscall", line);
		fclose(out);

	} else {
		return 0;
	}

	return 0;

}
