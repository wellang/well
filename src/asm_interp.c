/*Copyright (c) 2022 Tristan Wellman*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "mov_search.h"
#include "syscall_interp.h"
#include "push_search.h"
#include "types.h"
#include "log.h"
#include "instructions.h"
#include "asm_macros.h"
#include "include.h"
#include "lea.h"

#include "rodata.h"

#include "asm_interp_funcs.h"

#include "argparse/argparse.h"

#include "asm2obj.h"

int asm_interp(int argc, char *argv[], bool INFO_DEBUG) {

	const char *fname;

	fname = argv[1];

	FILE *file6 = fopen(fname, "r+");
	char line7[256];

        while(fgets(line7, sizeof(line7), file6) != NULL) {
                
                char include_search[] = "include~ ";
                char *include = strstr(line7, include_search);
                
		char comment[] = "//";
		char *search_com = strstr(line7, comment);
		
		if(include != NULL && search_com == NULL) {
         		/* WELLANG INCLUDE SYNTAX
			*
         		*  include~ relative_file_path.wesm
         		*  lib~ relative_file_path.a
         		* 
			* */
                        char *tild = strchr(line7, '~');

			if(tild != NULL) {
				tild++;
			}

			const char *fpath = tild;		

			include_comp(fpath);
                        
                        return 0;
                } else {
			continue;	
		}
                if(line7 == NULL) {
                        break;
                }       
                
        }  

	char line8[256];
	FILE *bits = fopen(fname, "r+");
	FILE *bit_out;
	while(fgets(line8, sizeof(line8), bits) != NULL) {
		bits_interp(bit_out, line8);
		if(line8 == NULL) {
			break;
		}
	}

	char line[256];

	FILE *file;
	file = fopen(fname, "r+");

	FILE *output;
	output = fopen("a.asm", "a");

	fprintf(output, "section .data\n"/*section .text\n\n"*/);
	fclose(output);

	while(fgets(line, sizeof(line), file) != NULL) {
				
		char var_search[] = "~var:main {";
		char *var = strstr(line, var_search);

		if(var != NULL) {
			FILE *out2;
			FILE *varread = fopen(fname, "r+");
			char mainlines[256];

			while(fgets(mainlines, sizeof(mainlines), varread) != NULL) {
				
				char brack_s[] = "}";
				char *search_b = strstr(mainlines, brack_s);
				if(search_b != NULL) {
					break;
				}
				
				if(mainlines == NULL) {
					break;
				} else {
					//_floa_interp_(mainlines, out2);
					asm_interp_var_funcs(mainlines, out2);
				}
			}

		}
	
		if(line == NULL) {
			break;
		}
	}
	
	FILE *out3 = fopen("a.asm", "a");
	fprintf(out3, "section .text\n\n");
	fclose(out3);

	/*macro compiler*/
	macro_interp(fname);

	FILE *file3 = fopen(fname, "r+");
	char line4[256];
	int line_num = 0;
	int lineline_num = 0;
	while(fgets(line4, sizeof(line4), file3) != NULL) {
		
		lineline_num++;
		char search[] = "~func:";
		char *func = strstr(line4, search);
		char search_main[] = "~func:main"; 
		char *main = strstr(line4, search_main);

		if(func != NULL && main == NULL) {
				if(INFO_DEBUG == true){log_info("found function at line: %d", lineline_num);}
				char *after_func = strchr(line4, ':');
				if(after_func != NULL) {
						after_func++;
						
						char search[] = "{";
						char *brack = strstr(after_func, search);
						if(brack != NULL) {
							char *function_name = strtok(after_func, "{");
							FILE *func = fopen("a.asm", "a");
							function_name[strlen(function_name)-1] = '\0';
							fprintf(func, "%s:\n", function_name);
							fclose(func);

							FILE *read = fopen(fname, "r+");
							char line6[256];
							int line_better = 0;
							int line_line = lineline_num;
							while(fgets(line6, sizeof(line6), read) != NULL) {
								/*char search_for_func[] = function_name;
								char func = strstr(line6, search_for_func);
								if(func != NULL) {
									
								}*/
								if(line_better != line_line) {
									line_better++;
								} else if(line_better == line_line) {
									line_better++;
									line_line++;
									char *end = strstr(line6, "}");
									char *main = strstr(line6, "func:main");
									if(end != NULL) {
										if(INFO_DEBUG == true){log_info("line:%d is the end of a function\n", line_better);}
										break;
									} else if(main != NULL) {
										if(INFO_DEBUG == true){log_info("line:%d found main function\n", line_better);}
										break;
									} else if(end == NULL && main == NULL){
										FILE *out;
										asm_interp_func_funcs(line6, out, line_better);
									}
								}
							}	
						} else if(brack == NULL) {
							log_warn("sub function brackets not implimented yet\n\n");
						}

				} else if(after_func == NULL) {
						log_error("ERROR:: Line.%d - Function does not have delimiter ':'\n", line_num);
						continue;
				}
		} else if(func != NULL && main != NULL) {
			if(INFO_DEBUG == true){log_info("found main fuction at line: %d", lineline_num);}
      			FILE *outputfunc = fopen("a.asm", "a");
	                fprintf(outputfunc, "\n\nglobal main\n\nmain:\n\t");
 	                fclose(outputfunc);

			FILE *main_func = fopen(fname, "r+");
			char mainline[256];
			int mainline_num = 0;
			int line_line = line_num;
			while(fgets(mainline, sizeof(mainline), main_func) != NULL) {
				if(mainline_num != line_line) {
					mainline_num++;
				} else if(mainline_num == line_line) {
					line_line++;
					mainline_num++;
					char *main_search = strstr(mainline, "func:main");
					if(main_search != NULL) {
						int the_line = mainline_num;
						int line_yo = 0;
						FILE *main_run = fopen(fname, "r+");
						char lineline[256];
						while(fgets(lineline, sizeof(lineline), main_run) != NULL) {
							
							if(line_yo != the_line) {
								line_yo++;
								continue;
							} else if(line_yo == the_line) {
								line_yo++;
								the_line++;

								char *main_search = strstr(lineline, "func:main");
								char *end_of_main = strstr(lineline, "}");
								if(end_of_main != NULL && main_search == NULL) {
									break;	
								} else if(end_of_main == NULL && main_search == NULL) {
									FILE *out;
									asm_interp_func_funcs(lineline, out, line_yo);
								}

							}
						}
					} else if(main_search == NULL) {
						continue;
					}
				}
				if(mainline == NULL) {
					break;
				}
			}
			fclose(main_func);

		} else if(func == NULL && main == NULL) {
			continue;
		}
		line_num++;
		if(line4 == NULL) {
			break;
		}

	}


	//rodata_to_asm();

	/*fclose(file);*/
	/*fclose(output);*/
	return 0;

}

void compile(int argc, char *argv[]) {

	struct ArgparseParser parser = argparse_init("wesm", argc, argv);

	argparse_add_option(&parser, "--object", "-o", ARGPARSE_FLAG);
	argparse_add_option(&parser, "--assembly", "-a", ARGPARSE_FLAG); // keeps the tmp assembly file
   	argparse_add_option(&parser, "--gcc", "-cc", ARGPARSE_FLAG); // ex: wesm main.well -cc ::-lpthread -lcurl -g:: -o main
	argparse_add_option(&parser, "--info", "-i", ARGPARSE_FLAG);


	const char *out;
	bool keep_asm;

	const char *gcc_options;

	const char *start = "nasm -f elf64 a.asm -o a.o";
	const char *linker = "gcc a.o -no-pie";

	char out_buf[0x100];
	char gcc_buf[0x100];
	char final_buf[0x100];

    	if(argparse_option_exists(parser, "--output") != ARGPARSE_NOT_FOUND ||
    		argparse_option_exists(parser, "-o") != ARGPARSE_NOT_FOUND) {

       		int i = 1;
		for(i = 1; i < 256; i++) {
			if(argv[i] == NULL) {
				snprintf(out_buf, sizeof(out_buf), "-o a.out");
				break;
			}
			if(!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) {

				out = argv[i + 1];
				snprintf(out_buf, sizeof(out_buf), "-o %s", out);	
				break;	

			}
		}
    	}
	if(argparse_option_exists(parser, "--assembly") != ARGPARSE_NOT_FOUND ||
			argparse_option_exists(parser, "-a" != ARGPARSE_NOT_FOUND)) {
	


		int i = 1;
		for(i = 1; i < 256; i++) {
			if(argv[i] == NULL) {
				keep_asm = false;
				break;
			}
                        if(!strcmp(argv[i], "--assembly") || !strcmp(argv[i], "-a")) {
                                        keep_asm = true;
                                        break;
                        } else {
				continue;
			} 			
		}
	
	} else {
		keep_asm = false;
	}
	if(argparse_option_exists(parser, "--gcc") != ARGPARSE_NOT_FOUND ||
			argparse_option_exists(parser, "-cc") != ARGPARSE_NOT_FOUND) {
		int i = 1;
		for(i = 1; i < 256; i++) {
			if(argv[i] == NULL) {
				break;
			}
			if(!strcmp(argv[i], "-gcc") || !strcmp(argv[i], "-cc")) {
				gcc_options = argv[i + 1];
				char *tmp = strstr(gcc_options, "::");
				if(tmp != NULL) {
					tmp++;
					//const char delim[] = "\"";
					//char *gcc = strtok(tmp, delim);
				} else {
					log_error("ERROR:: Bad gcc options: %s\n (ex: wesm main.well -cc ::-lpthread -lcurl -g::)\n", gcc_options);
				}
				const char delim[] = "::";
				char *gcc = strtok(tmp, delim);
				snprintf(gcc_buf, sizeof(gcc_buf), "%s", gcc);
				break;
			}
		}
			
	}

	bool INFO_DEBUG;

	if(argparse_option_exists(parser, "--info") != ARGPARSE_NOT_FOUND ||
			argparse_option_exists(parser, "-i") != ARGPARSE_NOT_FOUND) {
	
		int i = 1;
		for(i = 2; i < 256; i++) {
		
			if(argv[i] == NULL) {
				INFO_DEBUG = false;
				break;
			}
			if(!strcmp(argv[i], "--info") || !strcmp(argv[i], "-i")) {
					INFO_DEBUG = true;
					break;
			} else {
				continue;
			}
		
		}

	}

	clock_t time_start, time_end;
	time_start = clock();

	asm_interp(argc, argv, INFO_DEBUG);

	snprintf(final_buf, sizeof(final_buf), "%s && %s %s %s", start, linker, gcc_buf, out_buf);
	system(final_buf);
	if(INFO_DEBUG == true){log_info(final_buf);}
	if(keep_asm == false) {
		/*FILE *included_files = fopen("a.asm", "r+");
		char line[256];
		while(fgets(line, sizeof(line), included_files) != NULL) {
			if(line == NULL) {
				break;
			}
			char include[] = "include ";
			char *find = strstr(line, include);
			if(include != NULL) {
				const char delim[] = "\"";
				char *file_uno = strstr(include, "\"");
				char *file = strtok(file_uno, delim);
				char buf[0x100];
				snprintf(buf, sizeof(buf), "r -f %s", file);
				system(buf);
			} else {
				continue;
			}
		}*/
		system("rm -f a.asm a.o");
	} else {
		system("rm -f a.o");
	}

	time_end = clock();
	log_info("Compile time:: %f seconds\n", ((double)(time_end - time_start) / CLOCKS_PER_SEC));
	/*if(!strcmp(argv[2], "-o")) {
		OUTPUT_NAME = argv[3];
		EXEC_NAME = argv[4];
		snprintf(buf, sizeof(buf), "nasm -f elf64 a.asm -o %s && ld %s -o %s && rm -f %s", OUTPUT_NAME, OUTPUT_NAME, EXEC_NAME, OUTPUT_NAME);
		system(buf);
		log_info("%s Compiled successfully!\n", OUTPUT_NAME);
	} else {
		system("nasm -f elf64 a.asm -o a.o && gcc a.o -o out -no-pie");
		log_info("Program Compiled successfully!\n");
	}*/

	argparse_free(parser);
}

int main(int argc, char *argv[]) {

	// [ TEST ] //
	//asm2obj("./test/test.asm", "~win", "~x32");
	//parser("./test/test.asm", "./test/test.o");
	//return 0;
	// [ END TEST ] //

	if(argv[1] == NULL) {
		log_error("\n:: Invalid file name, ex: wesm (.well file) -o (.o file) (executable name)\n > wesm test.well -o test.o test\n\n");
		return 0;
	}

	compile(argc, argv);
	return 0;	

}
