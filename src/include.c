#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "mov_search.h"
#include "syscall_interp.h"
#include "push_search.h"
#include "types.h"
#include "log.h"
#include "instructions.h"
#include "asm_macros.h"
#include "lea.h"

struct include_file {

	FILE *wellfile;

	//char FUNC_NAME[];

} include_file;

int include_var_funcs(char line[], FILE *out) {

	string_interp(line, out);
	length_interp(line, out);
	int_interp(line, out);

	char_interp(out, line);
	print_asm_interp(out, line);
	
	return 0;

}

int include_func_funcs(char line[], FILE *out, int line_num) {

	mov_interp(line, out);
	push_interp(line, out);
	
	syscall_interp(line, out);
	pop_interp(out, line);
	array_run(out, line);
	cif_interp(out, line);
	halt_interp(out, line);
	bits_interp(out, line);
//	run_interp(out, line);
	print_asm_interp(out, line);
	lea_interp(line, out, line_num);
	return0(out, line);

	return 0;

}

	/*
	 *include: call~ wellfile.wellfunc
	 *include_lib: lib~ wellfile.wellfunc
	 * */


const char *get_asm_name(const char *fname, const char *final_name) {

	

	return final_name;

}

int include_comp(FILE *out, char line[]) {

	char call[] = "call~ ";
	char mov[] = "move~ ";

	char *find_call = strstr(line, call);
	if(find_call != NULL) {
		char tild[] = "~"; 
		char *file_and_func = strstr(line, tild); //wellfile.wellfunc

		if(file_and_func != NULL) {
			file_and_func++;
		}

		//log_info(":%s:", file_and_func);
		
		const char delim[] = ".";
		char *func = strchr(file_and_func, '.');	
		char *file = strtok(file_and_func, delim);
		if(func != NULL) {
			func++;
		}
		func[strcspn(func, "\n")] = 0;	
		if(file != NULL) {
			file++;
		}

		log_info(":%s:%s:", func, file);
		
		char fname_buf[0x100];
		snprintf(fname_buf, sizeof(fname_buf), "%s.well", file);

		include_file.wellfile = fopen(fname_buf, "r+");
		char line0[256];

		if(include_file.wellfile == NULL) {
		
			log_error("Invalid call file %s", file);
			return 1;
		
		}

		char func_buf[0x100];
		snprintf(func_buf, sizeof(func_buf), "~func:%s", func);

		int line_num = 0;
		while(fgets(line0, sizeof(line0), include_file.wellfile) != NULL) {
			line_num++;
			//printf(line0);

			if(line0 == NULL) {
				break;
			}

			char *func_find = strstr(line0, func_buf);
			if(func_find != NULL) {
				//log_info(line0);
				int func_line = line_num;
				char line1[256];
				while(fgets(line1, sizeof(line1), include_file.wellfile) != NULL) {
					func_line++;

					if(line1 == NULL) {
						return 0;
					}
					if(func_line >= line_num) {
						char search[] = "}";
						char *brack = strstr(line1, search);
						if(brack != NULL) {
							break;
						} else {
							FILE *out;
							include_func_funcs(line1, out, func_line);
						}
					} else if(func_line < line_num) {
						continue;
					}
				}
				continue;
			}


		}
		
		fclose(include_file.wellfile);

	} else {
		return 0;
	}

	return 0;
}

int lib_comp(const char *fname) {
	
	

	return 0;
}



