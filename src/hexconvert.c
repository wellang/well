/*Copyright (c) Tristan Wellman*/
#include "hexconvert.h"
#include "util.h"

const int offset = 'A';

/*All conversions take place as strings*/
char *uint64ToHex(char *value) {
	unsigned long int val = strtoul(value, NULL, 10);
	int remainder;
	char output = '0';
	char *hex = (char *)malloc(sizeof(char)*(strlen(value)+10));
	do {
		remainder = val % 16;
		val /= 16;
		if(remainder>=10) {
			output = (char)(offset+(remainder-10));
		} else output = (char)(remainder+'0');
		STARTAPPCHAR(hex, output);
		hex = STRET;
	} while(remainder>0&&val>0);
	char *ret = (char *)malloc(sizeof(char)*(strlen(hex)+10));
	sprintf(ret, "0x%s", hex);
	free(hex);
	return ret;
}

char *float64ToHex(char *value) {
	return " ";
}
