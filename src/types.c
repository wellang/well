/*Copyright 2022 Tristan Wellman*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "log.h"
#include "array_interp.h"

#include "rodata.h"
#include "types.h"

int string_interp(const char *fname, char line[], int line_num, FILE *out) {

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
				wlog_error(fname, line_num, "String missing '=' ex: string~ foo = 'bar'\n"
                                            "       |\n"
                                            "   %d|\t%s\n", line_num, line);
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
			string_name[strlen(string_name)-1] = '\0';
			fprintf(out2, "%s: db%s, 0\n\t.len: equ $-%s\n",
					string_name, after_name,
					string_name);
			fclose(out2);
		} else {
			wlog_error(fname, line_num, "String missing '~' ex: string~ foo = 'bar'\n"
                                        "       |\n"
                                        "   %d|\t%s\n", line_num, line);
			return 0;
		}

	} else {
		return 0;
	}

	return 0;

}

int mut_interp(char line[], int line_num) {

  /*well:
    ~var:main {
      string~ test = 'test'
      mut~ test = resb 1
    }

    nasm:
    section .text
      test: db 'test', 0
      .len: equ $-test
    section .bss:
      mtest: resb 1
   */
  
  struct mut_data data;

  const char *muttypes[6] = {
    "resb",
    "resw",
    "resq",
    "resy",
    "resz",
    "resd"
  };
  
  char *string = strstr(line, "mut");
  if(string != NULL) {

    char *tild = strchr(line, '~');
    if(tild != NULL) {
      tild++;
      char *eq = strchr(line, '=');
      if(eq != NULL) {
	
	char *resb = strstr(line, muttypes[0]);
	char *resw = strstr(line, muttypes[1]);
	char *resq = strstr(line, muttypes[2]);
	char *resy = strstr(line, muttypes[3]);
	char *resz = strstr(line, muttypes[4]);
	char *resd = strstr(line, muttypes[5]);
	if(resb != NULL || resw != NULL ||
	   resq != NULL || resy != NULL || resz != NULL || resd != NULL) {

	  const char delim[] = "=";
	  char *after_name = strchr(tild, '=');
	  char *mut_name = strtok(tild, delim);

	  if(after_name != NULL) {
	    after_name++;
	  }
	  after_name[strlen(after_name)-1] = '\0';
	  mut_name[strlen(mut_name)-1] = '\0';
	  char buf[0x100];
	  snprintf(buf, sizeof(buf), "\n%s: %s\n",
		   mut_name, after_name);
	  /*data.muts[line_num] = buf;*/
	  FILE *bss = fopen("a.asm", "a");
	  fprintf(bss, buf);
	  fclose(bss);
	} else { log_error("Mutable variable missing reserve type (ex: mut~ test = resb 1)\n"); }
	
      } else { log_error("Mutable variable missing '=' (ex: mut~ test = resb 1)\n"); }
      
    } else { log_error("Mutable variable missing '~' (ex: mut~ test = resb 1)\n"); }
    
  }

  return 0;
  
}

/*int length_interp(char line[], FILE *out) {
	
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
}*/


int int_interp(const char *fname, char line[], int line_num, FILE *out) {

  const char *var_type;
  char *long_ = strstr(line, "long");
  if(long_ != NULL) {var_type = "dq";} else {var_type = "dd";}

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
				wlog_error(fname, line_num, "Variable missing '=' ex: int~ foo = 1234\n"
                                            "       |\n"
                                            "   %d|\t%s\n", line_num, line);
				return 0;
			}

			after_name[strlen(after_name)-1] = '\0';
			var_name[strlen(var_name)-1] = '\0';
			out = fopen("a.asm", "a");
			fprintf(out, "\n\t%s: %s%s", var_name, var_type, after_name);
			fclose(out);

		} else {
			wlog_error(fname, line_num, "Variable missing '~' ex: int~ foo = 1234\n"
                                        "       |\n"
                                        "   %d|\t%s\n", line_num, line);
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

int char_interp(const char *fname, FILE *out, char line[], int line_num) {
	
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
				wlog_error(fname, line_num, "Char missing '=' ex: char~ foo = 'A'\n"
                                            "       |\n"
                                            "   %d|\t%s\n", line_num, line);
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
