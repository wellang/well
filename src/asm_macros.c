/*Copyright (c) 2022 Tristan Wellman*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

int macro_interp(const char *__restrict fname) {

	FILE *file = fopen(fname, "r+");
	char line[256];
	int line_num = 0;

	while(fgets(line, sizeof(line), file) != NULL) {
		
		line_num++;

		char search[] = "~macro:";
		char *macro = strstr(line, search);

		if(macro != NULL) {
			log_info("Found macro at line: %d\n", line_num);
			char *after_macro = strchr(line, ':');
			if(after_macro != NULL) {
				after_macro++;
				/*well: ~macro:foo[2] {}
				 *nasm: %macro foo 2
				 	%endmacro*/
				char num_search[] = "[";
				char *brack = strstr(after_macro, num_search);
				if(brack != NULL) {
					char *macro_name = strtok(after_macro, "[");

				} else {
					char *macro_name = strtok(after_macro, "{");
					FILE *mac = fopen("a.asm", "a");


				}
			} else {
				log_error("Macro missing name and/or ':' delimeter!\n");
				return 0;
			}
		} 

	}
	
	return 0;
}
