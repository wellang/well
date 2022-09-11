#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

#include "include.h"

int pop_interp(FILE *out, char line[], int line_num, const char *fname) {

	char search[] = "pop~ ";
	char *pop = strstr(line, search);
	if(pop != NULL) {
	
		out = fopen("a.asm", "a");
		
		char *after_pop = strchr(line, '~');
		if(after_pop != NULL) {
			after_pop++;
			fprintf(out, "pop %s\n", after_pop);
		} else if(after_pop == NULL) {
			wlog_error(fname, line_num, "ERROR:: Pop instruction expects item\n\n");
			return 0;
		}

	}
	return 0;

}

int cif_interp(FILE *out, char line[], int line_num, const char *fname) {
	
	char search[] = "cif";
	char cli_search[] = "cli";
	char *cli_string = strstr(line, cli_search);
	char *string = strstr(line, search);

	if(string != NULL) {
		out = fopen("a.asm", "a");
		fprintf(out, "\n\tcli\n");
		fclose(out);
	} else if(cli_string != NULL) {
		wlog_error(fname, line_num, "cli is not an instruction! Did you mean cif?\n");
		return 0;
	}

	return 0;
}

int halt_interp(FILE *out, char line[], int line_num, const char *fname) {
	
	char search[] = "halt";
	char hlt_search[] = "hlt";
	char *halt = strstr(line, search);
	char *hlt = strstr(line, hlt_search);

	if(halt != NULL) {
		out = fopen("a.asm", "a");
		fprintf(out, "\n\thlt\n");
		fclose(out);
	} else if(hlt != NULL) {
		wlog_error(fname, line_num, "hlt is not an instruction! Did you mean halt?\n");
		return 0;
	}
	
	return 0;
}

int bits_interp(FILE *out, char line[], int line_num, const char *fname) {

	char search[] = "bits~ ";
	char *bits = strstr(line, search);

	if(bits != NULL) {
		char *bit_size = strchr(bits, '~');
		char *bit = bit_size + 1;
		out = fopen("a.asm", "a");
		fprintf(out, "bits %s\n", bit);
		fclose(out);
	}

	return 0;

}


// replaced with call_interp
/*int run_interp(FILE *out, char line[]) {

	return 0;

}*/

int call_interp(FILE *out, char line[], int line_num, const char *fname) {

	/*well: 
	 * 	call~ wellfile.wellfunc 
	 *nasm:
	 * 	%include "asmfile.asm"
	 *	call asmfunc
	 */

	char per[] = ".";
	char *search = strstr(line, per);
	if(per != NULL) {

		include_comp(out, line, line_num, fname);

	} else {
	        char search[] = "call~ ";
	        char *call = strstr(line, search);
	        if(call != NULL) {
			
			call++;
			call++;

			printf(call);

	                out = fopen("a.asm", "a");
			fprintf(out, "call %s", call);
	                fclose(out);
	        } else if(call == NULL) {
	                return 0;
		}	
	}

	return 0;

}

int resb_interp(FILE *out, char line[], int line_num, const char *fname) {

	char search[] = "resb~ ";
	char *resb = strstr(line, search);
	if(resb != NULL) {
		char *resb_num = strchr(resb, '~');
		char *res = resb_num + 1;
		out = fopen("a.asm", "a");
		fprintf(out, "\n\tresb %s\n", res);
		fclose(out);
	}
	return 0;

}

int print_asm_interp(FILE *out, char line[], int line_num, const char *fname) {
	
	char search[] = "asm~ ";
	char *asm_search = strstr(line, search);
	if(asm_search != NULL) {
		char *after_asm = strchr(asm_search, '~');
		char *res = after_asm + 1;
		out = fopen("a.asm", "a");
		fprintf(out, "\n%s\n", res);
		fclose(out);
	}
	return 0;

}

int ret_interp(FILE *out, char line[], int line_num, const char *fname) {

	char search_ret[] = "ret";
	char *ret_search = strstr(line, search_ret);

	if(ret_search != NULL) {
	
		out = fopen("a.asm", "a");
		fprintf(out, "\tret\n");
		fclose(out);

	}
	return 0;

}

int return0(FILE *out, char line[], int line_num, const char *fname) {

/*
 * mov rax, 60
 * mov rdi, 0
 * syscall
 */
	char search[] = "return ";
	char *return_search = strstr(line, search);

	if(return_search != NULL) {
		char after_ret[] = " ";
		char *return_num = strstr(line, after_ret);
		if(return_num != NULL) {
			return_num++;
			out = fopen("a.asm", "a");
		    #ifndef __linux__
			    fprintf(out, "\n\tmov rax, 60\n\tmov rdi, %s\n\tsyscall\n", return_num);
		        fclose(out);
			#else
				fprintf(out, "\n\tmov rax, 1\n\tmov rdi, %s\n\t\syscall\n", return_num);
			#endif

		} else {
			out = fopen("a.asm", "a");
			#ifndef __linux__
			    fprintf(out, "\n\tmov rax, 60\n\tmov rdi, 0\n\tsyscall\n");
			    fclose(out);
			#elseif _WIN32
				fprintf(out, "\n\tmov rax, 1\n\tmov rdi, 0\n\tsyscall\n");
				fclose(out);
			#elseif __APPLE__
				fprintf(out, "\n\tmov rax, 1\n\tmov rdi, 0\n\tsyscall\n");
				fclose(out);
			#elseif __FreeBSD__
				fprintf(out, "\n\tmov rax, 1\n\tmov rdi, 0\n\tsyscall\n");
				fclose(out);
			#endif
		}
	}

	return 0;
}

/*int return1(FILE *out, char line[]) {

}*/

