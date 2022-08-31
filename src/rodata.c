#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

char *string_to_rodata_hex(char *string) {

	char *hexarr[512];
	int i;
	char *strings = (char *)malloc(sizeof(hexarr));
	char buf[512];
	snprintf(buf, sizeof(buf), "%x", string);
	for(i = 0; i < 512; i++) {
		if(buf[i] == NULL) {
			break
		} else {
			strings[i] = buf[i];
		}
	}
	for(i = 0; i < 512; i++) {
		if(strings[i] == NULL) {
			break;
		}
		if(i = 0) {
			hexarr[0] = strings[0];
		}
		hexarr[i] = strings[i];
		char setback = hexarr[i + 1];
		char buf2[512];
		snprintf(buf2, sizeof(buf2), "%sH")
	}

	free(strings);

	return string;	

}

void rodata_to_asm() {

	FILE *rodata = fopen("rodata.asm", "r+");
	char line[256];
	FILE *ASM = fopen("a.asm", "a");

	while(fgets(line, sizeof(line), rodata) != NULL) {
		if(line == NULL) {
			break;
		}
		fprintf(ASM, line);
	}

}
