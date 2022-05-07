#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int mov_interp(char line[], FILE *out) {

	char search[] = "move~ ";

	char *mov = strstr(line, search);
	if(mov != NULL) {
	
		out = fopen("a.asm", "a");

		fprintf(out, "; %s \n\tmov", line);
	
		fclose(out);

		char *after_mov = strchr(line, '~');

		if(after_mov != NULL) {
			after_mov++;

		/*	FILE *out2 = fopen("a.asm", "a");
			fprintf(out2, "; %s", after_mov);
			fclose(out2);
		*/
			const char delim[] = ",";
			
			char *after_var1 = strchr(after_mov, ',');
			char *mov_out = strtok(after_mov, delim);
			
			if(after_var1 != NULL) {
			
				after_var1++;
		/*		FILE *out4 = fopen("a.asm", "a");
				fprintf(out4, "%s", after_var1);
				fclose(out4);
		*/		
				const char delim2[] = ";";
			} else if(after_var1 == NULL){
				printf("ERROR:: move missing ',' or second var in line:\n\n");
				//return 0;
			}


		/*	FILE *out3 = fopen("a.asm", "a");
			fprintf(out3, mov_out);
			fclose(out3);
		*/
			const char delim2[] = ";";
			char *var2_out = strtok(after_var1, delim);

			char buf[0x100];
			after_var1[strlen(after_var1)-1] = '\0';
			snprintf(buf, sizeof(buf), "%s,%s", after_var1, mov_out);
			FILE *out5 = fopen("a.asm", "a");
			fprintf(out5, buf);
			fclose(out5);

		} else {
			printf("ERROR:: move missing '~' in line:\n\n");
			return 0;
		}		

	 } else if(mov == NULL) {
	 	return 0;
	 }
	
	return 0;

}


