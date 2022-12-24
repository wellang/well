#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "operators.h"

char op_check_buf[0x100];
char *keyword_return;
char *op_check_return;

char *check_keyword(char *string) {
  char *keywords[] = {
    "~if", "~while", "~for"
  };

  int i;
  for(i = 0; i < 4; i++) {
    char *check = strstr(string, keywords[i]);
    if(check != NULL) {
      keyword_return = check;
      return keyword_return; 
    }
  }

}

char *statement_buf;
char *statement_to_asm(char *string, bool is_if, bool is_while,
		       const char *funcname, int ifnum_ln, int ifnum) {
  if(is_if == true) {
    char buf[0x100];
    char *eq_ = strstr(string, "=="), *neq_ = strstr(string, "!=");
    char *gre_ = strstr(string, ">"), *les_ = strstr(string, "<");
    if(eq_ != NULL) {
      char *delim = eq;
      char *op2 = strstr(string, eq);
      char *op1 = strtok(string, delim);
      op1[strlen(op1)-1] = '\0';
      op2++;op2++;op2++;
      snprintf(buf, sizeof(buf), "\n\t cmp %s, %s\n\t"
	       "je %s_%d_%d%s%s_eq\n\t"
	       "jne %s_%d_%d_fin\n\t"
	       "%s_%d_%d%s%s_eq:",
	       op1, op2,
	       funcname, ifnum_ln, ifnum, op1, op2,
	       funcname, ifnum_ln, ifnum,
	       funcname, ifnum_ln, ifnum, op1, op2);
      statement_buf = buf;
      return statement_buf;
    } else if(neq_ != NULL) {
      char *delim = neq;
      char *op2 = strstr(string, neq);
      char *op1 = strtok(string, delim);
      op1[strlen(op1)-1] = '\0';
      op2++;op2++;op2++;
      snprintf(buf, sizeof(buf), "\n\t cmp %s, %s\n\t"
	       "jne %s_%d_%d%s%s_neq\n\t"
	       "je %s_%d_%d_fin\n\t"
	       "%s_%d_%d%s%s_neq:",
	       op1, op2,
	       funcname, ifnum_ln, ifnum, op1, op2,
	       funcname, ifnum_ln, ifnum,
	       funcname, ifnum_ln, ifnum, op1, op2);
      statement_buf = buf;
      return statement_buf;
    } else if(gre_ != NULL) {
      char *delim = gre;
      char *op2 = strstr(string, gre);
      char *op1 = strtok(string, delim);
      op1[strlen(op1)-1] = '\0';
      op2++;op2++;  
      snprintf(buf, sizeof(buf), "\n\t cmp %s, %s\n\t"
	       "jg %s_%d_%d%s%s_gre\n\t"
	       "jng %s_%d_%d_fin\n\t"
	       "%s_%d_%d%s%s_gre:",
	       op1, op2,
	       funcname, ifnum_ln, ifnum, op1, op2,
	       funcname, ifnum_ln, ifnum,
	       funcname, ifnum_ln, ifnum, op1, op2);
      statement_buf = buf;
      return statement_buf;
    } else if(les_ != NULL) {
      char *delim = les;
      char *op2 = strstr(string, les);
      char *op1 = strtok(string, delim);
      op1[strlen(op1)-1] = '\0';
      op2++;op2++;
      snprintf(buf, sizeof(buf), "\n\t cmp %s, %s\n\t"
	       "jl %s_%d_%d%s%s_les\n\t"
	       "jnl %s_%d_%d_fin\n\t"
	       "%s_%d_%d%s%s_les:",
	       op1, op2,
	       funcname, ifnum_ln, ifnum, op1, op2,
	       funcname, ifnum_ln, ifnum,
	       funcname, ifnum_ln, ifnum, op1, op2);
      statement_buf = buf;
      return statement_buf;
    }
  } else if(is_while == true) {
    exit(0);
  }
}

char *check_operator(char *string, const char *funcname, int ifnum_ln, int ifnum) {
  /*
  char *keyword_type = check_keyword(string);
  printf("%s", keyword_type);
  */
  char *eq_ = strstr(string, eq);
  char *neq_ = strstr(string, neq);
  char *gre_ = strstr(string, gre);
  char *les_ = strstr(string, les);
  char *gre_or_eq_ = strstr(string, gre_or_eq);
  char *les_or_eq_ = strstr(string, les_or_eq);
  if(eq_ == NULL && neq_ == NULL &&
     gre_ == NULL && les_ == NULL &&
     gre_or_eq_ == NULL && les_or_eq_ == NULL) {
    /*snprintf(op_check_buf, sizeof(op_check_buf), "NO_OP");*/
    op_check_return = "NO_OP";
    return op_check_return;
  } else if(eq_ != NULL || neq_ != NULL ||
	    gre_ != NULL || les_ != NULL ||
	    gre_or_eq_ != NULL || les_or_eq_ != NULL) {
    char *if_ = strstr(string, "~if");
    if(if_ != NULL) {
      const char delim[] = ")";
      char *first = strchr(string, '(');
      if(first != NULL) { first++; }
      char *string_statement = strtok(first, delim);
      char *asm_string = statement_to_asm(string_statement, true, false,
					  funcname, ifnum_ln, ifnum);
      op_check_return = asm_string;
      return op_check_return;
    } else if(!strcmp(string, "~while")) {
      exit(0);
    }
  }

}
