#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int push_interp(char line[], FILE *out) {

	char search[] = "push~ ";
	char *push = strstr(line, search);

	if(push != NULL) {
		
		out = fopen("a.asm", "a");
		fprintf(out, "\n; %s \n\tpush", line);
		fclose(out);

		char *after_p = strchr(line, '~');

		if(after_p != NULL) {
		
			after_p++;

			FILE *out2 = fopen("a.asm", "a");
			fprintf(out2, "%s\n", after_p);
			fclose(out2);
			

		}

	} else {
	
	}

	return 0;
}
