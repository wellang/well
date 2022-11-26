#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "log.h"

char *math(char line[], char final_buf[]) {

	char plus[] = "+";
	char sub[] = "-";

	char mult[] = "*";
	char div[] = "/";

	char *PLUS = strstr(line, plus);
	char *SUB = strstr(line, sub);
	char *MULT = strstr(line, mult);
	char *DIV = strstr(line, div);

	if(PLUS != NULL || 
			SUB != NULL ||
			MULT != NULL ||
			DIV != NULL) {
		
		const char delim[] = ":";
		char *after = strchr(line, ':');
		char *before = strtok(line, delim);

		if(after != NULL) {
			after++;
		}
	       	char *after_after = strchr(after, ':');
		
		if(after_after != NULL) {
			after_after++;
		}

		char *math_problem = strtok(after, delim);

		/*
			 move~ :32+{5*[49*3*(-4-9)]+56}*(-5):, rax
			
			         32+{5*[147*(-13)]+56}*(-5)
			         32+{5*[-1911]+56}*(-5)
			         32+(-9467)*(-5)
				 47335
		 */	

		char brack_s[] = "{";
		char brackets_s[] = "[";
		char par_s[] = "(";

		char *brack = strstr(math_problem, brack_s);
		char *brackets = strstr(math_problem, brackets_s);
		char *par = strstr(math_problem, par_s);

		if(brack != NULL) {
			if(brackets != NULL) {
				if(par != NULL) {
					
					const char delimlim[] = "{";
					char *math_prob = math_problem;
					char *before_brack = strtok(math_prob, delimlim);
					char *math_probob = math_problem;
					char *after_brack = strchr(math_probob, '}');
					/* before = 32+
					 after = *(-5)*/

					const char delim_zer[] = "[";
					char *first_math = math_problem;
					char *after_bracket = strchr(first_math, ']');
					if(after_bracket != NULL) {
						after_bracket++;
					}
					char *before_bracket = strtok(first_math, delim_zer);
					/* before = 5*
					 after = +56*/

					const char delim_one[] = "]";
					char *after_brackets = strchr(math_problem, '[');
					if(after_brackets != NULL) {
						after_brackets++;
					}
					char *before_brackets = strtok(after_brackets, delim_one);
					/* before_brackets = [49*3*(-4-9)]*/
					
					const char delimlimlimlim[] = ")";
					char *after_per = strstr(before_brackets, "(");
					char *math_probb = strtok(after_per, delimlimlimlim);
					/* math_probb = -4-9*/
					
					char *PLU = strstr(math_probb, plus);
					if(PLU != NULL) {
							
					}
					char *MIN = strstr(math_probb, sub);
					if(MIN != NULL) {
					
					}

					char after_problem[] = "}";
					char *AFTER_PROB = strstr(line, after_problem);

					char buf[0x100];
					snprintf(buf, sizeof(buf), "%s%s;true", before, AFTER_PROB);
					final_buf = buf;
					return final_buf;
				}
			}

		} else if(brackets != NULL && brack == NULL) {
			if(par != NULL && brack == NULL) {
			
			}
		} else if(par != NULL && brackets == NULL && brack == NULL) {
			
		} else if(par == NULL && brackets == NULL && brack == NULL) {
		
		}
	
	} else {
		char buf[0x100];
		snprintf(buf, sizeof(buf), "%s ;false", line);
		final_buf = buf;
		return final_buf;
	}

	return final_buf;  /*should be move~ 47335, rax*/
	
}
