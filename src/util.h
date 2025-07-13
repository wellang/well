/*Copyright (c) 2024 Tristan Wellman*/

#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <unistd.h>
#include <dirent.h>

#define WLOG(logLevel, ...) \
	fprintf(stdout, "%s "#logLevel"  (%s:%d): %s\n", \
		__TIME__,__FILE__,__LINE__,__VA_ARGS__);

#define WASSERT(err, ...) \
	if(!(err)) {fprintf(stderr,__VA_ARGS__);exit(1);}	

#define RESETFCURSOR(file) \
	fseek(file, 0, SEEK_SET);

#define ARRLEN(x) \
		(sizeof(x)/sizeof(x[0]))

#define STARTAPPCHAR(str_, c_) \
	do{char *STRET_ = calloc((strlen(str_)+2),sizeof(char)); \
	STRET_[0] = c_; \
	memcpy(STRET_+1, str_, strlen(str_)); \
	STRET_[strlen(str_)+1] = '\0'; \
	str_ = STRET_;}while(0)	\

#define WTRIM(s_) \
	do{while(*(s_)&&isspace((unsigned char)*(s_)))(s_)++; \
	if(*(s_)){char *endp = (s_)+strlen(s_)-1; \
	while(endp>(s_)&&isspace((unsigned char)*endp))*endp--='\0';}}while(0);

#define EATTABS(line) \
	do{int i,j=0; \
	for(i=0;line[i];i++) { \
		if(line[j+1]=='\0') break; \
		if(line[i]!='\t') line[j++] = line[i];} \
	line[j]='\0';}while(0)

#endif
