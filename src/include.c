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
	run_interp(out, line);
	print_asm_interp(out, line);
	lea_interp(line, out, line_num);
	return0(out, line);

	return 0;

}

	/*
	 *include~ relative_file_path.wesm
	 *lib~ relative_file_path.a
	 * */


const char *get_asm_name(const char *fname, const char *final_name) {

	

	return final_name;

}

int include_comp(const char *fname) {

	char line[256];

	const char *asm_fname;
	get_asm_name(fname, asm_fname);
	char buf[0x100];
	snprintf(buf, sizeof(buf), "%s.asm", buf);
	FILE *included_file = fopen(buf, "r+");

	while(fgets(line, sizeof(line), included_file) != NULL) {
		break;
	}	

	return 0;
}

int lib_comp(const char *fname) {
	
	

	return 0;
}



