/*Copyright (c) 2024 Tristan Wellman*/

#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WLOG(logLevel, ...) \
	fprintf(stdout, "%s "#logLevel"  (%s:%d): %s\n", \
		__TIME__,__FILE__,__LINE__,__VA_ARGS__);

#define WASSERT(err, ...) \
	if(!(err)) {fprintf(stderr,__VA_ARGS__);exit(1);}	

#define RESETFCURSOR(file) \
	fseek(file, 0, SEEK_SET);

#define ARRLEN(x) \
		(sizeof(x)/sizeof(x[0]))

#define EATTABS(line) 							\
	int i,j=0; 									\
	for(i=0;line[i];i++) {						\
		if(line[j+1]=='\0') break; 				\
		if(line[i]!='\t') line[j++] = line[i];} \
	line[j]='\0';

#endif
