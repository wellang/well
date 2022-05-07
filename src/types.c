#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int string_interp(char line[], FILE *out) {

	char search[] = "string~ ";
	char *string = strstr(line, search);
	if(string != NULL) {
	
		out = fopen("a.asm", "a");
		fprintf(out, "; %s \n\t", line);
		fclose(out);

		char *after_s = strchr(line, '~');
		if(after_s != NULL) {
		
			after_s++;

			const char delim[] = "=";
			
			char *after_name = strchr(after_s, '=');
			char *string_name = strtok(after_s, delim);
			if(after_name != NULL) {
				after_name++;
			} else {
				printf("ERROR:: string missing '=' (string~ foo = 'bar')\n");
				return 0;
			}
			
			after_name[strlen(after_name)-1] = '\0';
			FILE *out2 = fopen("a.asm", "a");
			fprintf(out2, "%s: db%s, 10\n", string_name, after_name);
			fclose(out2);

		} else {
			printf("ERROR:: string missing '~' (string~ foo = 'bar')\n");
			return 0;
		}

	} else {
		return 0;
	}

	return 0;

}

int length_interp(char line[], FILE *out) {
	
	char search[] = "length~ ";
	char *string = strstr(line, search);
	if(string != NULL) {
		
		char *after_length = strchr(line, '~');
		if(after_length != NULL) {
			after_length++;

			const char delim[] = ",";
			char *after_name = strchr(after_length, ',');
			char *length_name = strtok(after_length, delim);

			if(after_name != NULL) {
				after_name++;
			} else {
				return 0;
			}
               		after_name[strlen(after_name)-1] = '\0';
                	out = fopen("a.asm", "a");
                	fprintf(out, "\t%s: equ $-%s\n", length_name, after_name);
                	fclose(out);

		} else {
			return 0;
		}

	} else {
		return 0;
	}

	return 0;
}

















