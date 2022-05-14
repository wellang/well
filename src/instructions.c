#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pop_interp(FILE *out, char line[]) {

	char search[] = "pop~ ";
	char *pop = strstr(line, search);
	if(pop != NULL) {
	
		out = fopen("a.asm", "a");
		
		char *after_pop = strchr(line, '~');
		if(after_pop != NULL) {
			after_pop++;
			fprintf(out, "pop %s\n", after_pop);
		} else if(after_pop == NULL) {
			printf("ERROR:: Pop instruction expects item\n\n");
			return 0;
		}

	}
	return 0;

}

int call_interp(FILE *out, char line[]) {

	return 0;

}

int ret_interp(FILE *out, char line[]) {

	char search[] = "return";
	char *ret = strstr(line, search);

	if(ret != NULL) {
	
		out = fopen("a.asm", "a");
		fprintf(out, "\nret\n");
		fclose(out);

	}
	return 0;

}
