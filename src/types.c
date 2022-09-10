/*Copyright 2022 Tristan Wellman*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "log.h"
#include "array_interp.h"

#include "rodata.h"

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
				log_error("ERROR:: string missing '=' (string~ foo = 'bar')\n");
				return 0;
			}
			
			after_name[strlen(after_name)-1] = '\0';
			FILE *out2 = fopen("a.asm", "a");
			/*char line[256];
			fgets(line, sizeof(line), out2);
			if(line == NULL) {
				fprintf(out2, "section .rodata\n%s:\n\tdb%s, 00H\n");
				fclose(out2);
			} else {
				fprintf(out2, "%s:\n\tdb%s, 00H\n", string_name, after_name);
				fclose(out2);

			*/
			fprintf(out2, "%s: db%s\n", string_name, after_name);
			fclose(out2);
		} else {
			log_error("ERROR:: string missing '~' (string~ foo = 'bar')\n");
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


int int_interp(char line[], FILE *out) {

	char search[] = "int~ ";
	char *string = strstr(line, search);
	if(string != NULL) {
		
		char *after_i = strchr(line, '~');
		if(after_i != NULL) {
		
			after_i++;

			const char delim[] = "=";

			char *after_name = strchr(after_i, '=');
			char *var_name = strtok(after_i, delim);
			if(after_name != NULL) {
				after_name++;
			} else {
				log_error("ERROR:: Variable missing '=', EX:(int~ foo = 1234)\n");
				return 0;
			}

			after_name[strlen(after_name)-1] = '\0';
			var_name[strlen(var_name)-1] = '\0';
			out = fopen("a.asm", "a");
			fprintf(out, "\t%s: dw%s\n", var_name, after_name);
			fclose(out);

		} else {
			log_error("ERROR:: Variable missing '~', EX:(int~ foo = 1234)\n");
			return 0;
		}

	} else {
		return 0;
	}
	return 0;

}

/*int _floa_interp_(char line[], FILE *out) {

	// well: float~ test = 3.1459
        //  nasm: test: dd3.1458

	char search[] = "float~ ";
	char *floatstr = strstr(line, search);
	if(floatstr != NULL) {
	
		char *after_f = strchr(line, '~');
		if(after_f != NULL) {
			after_f++;
			const char delim[] = "=";
			
			char *after_name = strchr(after_f, '=');
			char *var_name = strtok(after_f, delim);
			if(after_name != NULL) {
				after_name++;
			} else {
				log_error("ERROR:: Variable missing '=' EX:(float~ foo = 3.1459)\n");
				return 0;
			}

			after_name[strlen(after_name-1)] = '\0';
			var_name[strlen(var_name)-1] = '\0';
			out = fopen("a.asm", "a");
			fprintf(out, "\t%s: dd%s\n", var_name, after_name);
			fclose(out);

		} else {
			log_error("ERROR:: Variable missing '~', EX:(float~ foo = 3.1459)\n");
			return 0;
		}
		
	} else {
		return 0;
	}
	return 0;

}*/

int char_interp(FILE *out, char line[]) {
	
	char search[] = "char~ ";
	char *char_search = strstr(line, search);
	if(char_search != NULL) {
		
		char *after_c = strchr(line, '~');
		if(after_c != NULL) {
			after_c++;
			const char delim[] = "=";
			char *after_name = strchr(after_c, '=');
			char *var_name = strtok(after_c, delim);
			if(after_name != NULL) {
				after_name++;
			} else {
				log_error("char missing '='\n");
				return 0;
			}
			after_name[strlen(after_name)-1] = '\0';
			var_name[strlen(var_name)-1] = '\0';
			out = fopen("a.asm", "a");
			fprintf(out, "\t%s: db%s\n", var_name, after_name);
			fclose(out);
		}

	} /*else if(char_search != NULL && dot != NULL) {
		char *after_c = strchr(line, '*');
		if(after_c != NULL) {
			after_c++;
			const char delim[] = "=";
			char *after_name = strchr(after_c, '=');
			char *var_name = strtok(after_c, delim);

			if(after_name != NULL) {
				after_name++;
			} else {
				log_error("char missing '='\n");
				return 0;
			}
			after_name[strlen(after_name) - 1] = '\0';
			var_name[strlen(var_name)-1] = '\0';
			out = fopen("a.asm", "a");
			fprintf(out, "\t%s: .quad %s", var_name, after_name);
			fclose(out);

		}

	}*/
	
	return 0;
}

int array_run(FILE *out, char line[]) {

	array_interp(out, line);
	return 0;

}
