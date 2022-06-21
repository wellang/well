#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int include_comp(const char *fname, char *dir, int argc, char *argv[]) {

	FILE *includes = fopen(dir, "r+");
	char line[256];
	
	FILE *well_file = fopen(fname, "r+");
	char line2[256];

	FILE *out = fopen("a.well", "a");
	
	int well_line = 0;
	while(fgets(line2, sizeof(line2), well_file) != NULL) {
	
		char *include = strstr(line2, "include~");

		if(include != NULL) {
			continue;
		}
		
		fprintf(out, line2);

		char *var_brac = strchr(line2, '}');
		if(var_brac != NULL) {
			break;
		} else if(line2 == NULL) {
			break;
		}
		
		well_line++;
	}
	

	while(fgets(line, sizeof(line), includes) != NULL) {
	
		if(line == NULL) {
			break;
		} else {
			fprintf(out, line);
		}

	}

	char line3[256];
	int well_line2 = 0;
	while(fgets(line3, sizeof(line3), well_file) != NULL) {
		if(line3 == NULL) {
			break;
		} else if(well_line2 == well_line) {
			fprintf(out, line3);
		}
		well_line2++;
	}

	return 0;

}
