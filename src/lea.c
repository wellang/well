#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "log.h"

#include "math.h"

int lea_interp(char line[], FILE *out, int line_num) {
	
	/*char buf[];

	math(line, buf);

	char true_[] = ";true";
	char false_[] = ";false";
	char *TRUE = strstr(buf, true_);
	char *FALSE = strstr(buf, false_);

	line[] = buf;*/

	char search[] = "lea~";
	char *lea = strstr(line, search);

	if(lea != NULL) {
		
		out = fopen("a.asm", "a");
		fprintf(out, "; %s \tlea");
		fclose(out);

		char *after_lea = strchr(line, '~');

		if(after_lea != NULL) {
			
			after_lea++;
				
			const char delim[] = ",";

			char *after_var1 = strchr(after_lea, ',');
			char *lea_out = strtok(after_lea, delim);

			if(after_var1 != NULL) {
				after_var1++;
			} else {
				log_error("ERROR:: lea instruction missing ',' or second operator in line: %d\n\n", line_num);
				return 0;
			}

			const char delim2[] = ";";
			char *var2_out = strtok(after_var1, delim);

			char buf[0x100];
			after_var1[strlen(after_var1)-1] = '\0';
			snprintf(buf, sizeof(buf), "%s,%s", after_var1, lea_out);
			FILE *out5 = fopen("a.asm", "a");
			fprintf(out5, buf);
			fclose(out5);

		} else {
			log_error("ERROR:: lea missing '~'in line: %d\n\n", line_num);
			return 0;
		}

	}

}
