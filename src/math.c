#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "log.h"

int math(char line[], char[] final_buf) {

	char plus[] = "+";
	char sub[] = "-";

	char mult[] = "*";
	char div[] = "/";

	char *PLUS = strstr(line, plus);
	char *SUB = strstr(line, sub);
	char *mult = strstr(line, mult);
	char *div = strstr(line, div);

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

		char *math_prblem = strtok(after, delim);

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
					char before_brack = strtok(math_prob, delimlim);
					const char delimlimlim[] = "}";
					char *math_probob = math_problem;
					char after_brack = strtok(math_probob, delimlimlim);
					// before = 32+
					// after = *(-5)

					const char delim_one[] = "]";
					char after_brackets = strchr(math_problem, '[');
					if(after_brackets != NULL) {
						after_brackets++;
					}
					char before_brackets = strtok(after_brackets, delim_one);
					// after = []

					unsigned long long par_num = 					
				}
			}

		} else if(brackets != NULL && brack == NULL) {
			if(par != NULL && brack == NULL) {
			
			}
		} else if(par != NULL && brackets == NULL && brack == NULL) {
			
		} else if(par == NULL && brackets == NULL && brack == NULL) {
		
		}
	
	} else {
		final_buf = "false";
		return final_buf;
	}

	return final_buf; // should be move~ 47335, rax

}

int math_check(char line[], char buf[], bool MATH_IS_THERE) {

	math(line, buf);

	char true_[] = "true";
	char false_[] = "false";
	
	char *TRUE = strstr(line, true_);
	char *FALSE = strstr(line, false_);
	
	if(TRUE != NULL) {
	
		MATH_IS_THERE = true;
	
	} else if(FALSE != NULL) {
	
		MATH_IS_THERE = false
	
	}

	return MATH_IS_THERE && buf;

}
