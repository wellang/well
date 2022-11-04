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
#include "if.h"

#include "libwesm/com.h"
#include "libwesm/log_parse.h"

#include "asm_interp_funcs.h"
#include "argparse/argparse.h"

/*#include "asm2obj.h"*/

bool comment_check;

const char *ifscope;

int asm_interp(int argc, char *argv[], bool INFO_DEBUG) {

	struct LOG_DATA log;

	const char *fname;
	fname = argv[1];
	char tfile[0x100];
	char *logfile = logparse_set_log_file(fname, tfile);
	log = LOGPARSE_SET_FILE(fname);

	/*FILE *file6 = fopen(fname, "r+");
	char line7[256];

        while(fgets(line7, sizeof(line7), file6) != NULL) {
                
                char include_search[] = "include~ ";
                char *include = strstr(line7, include_search);
                
		char comment[] = "//";
		char *search_com = strstr(line7, comment);
		
		if(include != NULL && search_com == NULL) {
     
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
                
        } */ 

	char line8[256];
	FILE *bits = fopen(fname, "r+");
	FILE *bit_out;
	int lnum = 0;
	while(fgets(line8, sizeof(line8), bits) != NULL) {
		comment_check = __check_com__(line8);
		if(comment_check == true) {
			continue;
		}
		lnum++;
		bits_interp(bit_out, line8, lnum, fname);
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

		comment_check = __check_com__(line);
		if(comment_check == true) {
			  continue;
		}

		char var_search[] = "~var:main {";
		char *var = strstr(line, var_search);

		if(var != NULL) {
			FILE *out2;
			FILE *varread = fopen(fname, "r+");
			char mainlines[256];
			int lnum2 = 0;
			while(fgets(mainlines, sizeof(mainlines), varread) != NULL) {
				comment_check = __check_com__(mainlines);
				if(comment_check == true) {
					  continue;
				}
				lnum2++;
				char brack_s[] = "}";
				char *search_b = strstr(mainlines, brack_s);
				if(search_b != NULL) {
					break;
				}
				
				if(mainlines == NULL) {
					break;
				} else {
					/*_floa_interp_(mainlines, out2);*/
					asm_interp_var_funcs(mainlines, out2, lnum2, fname);
				}
			}

		}
	
		if(line == NULL) {
			break;
		}
	}

	int includecomp = file_lib_include_comp(fname);

	if(includecomp == 0) {
		FILE *out3 = fopen("a.asm", "a");
		fprintf(out3, "\nsection .text\n\n");
		fclose(out3);
	}
	/*macro compiler*/
	macro_interp(fname);

	FILE *file3 = fopen(fname, "r+");
	char line4[256];
	int line_num = 0;
	int lineline_num = 0;
	while(fgets(line4, sizeof(line4), file3) != NULL) {

		comment_check = __check_com__(line4);
		if(comment_check == true) {
			  continue;
		}

		lineline_num++;
		char search[] = "~func:";
		char *func = strstr(line4, search);
		char search_main[] = "~func:main"; 
		char *main = strstr(line4, search_main);

		if(func != NULL && main == NULL) {
				if(INFO_DEBUG == true){wlog_info(fname, lineline_num, "found function at line: %d", lineline_num);}
				char *after_func = strchr(line4, ':');
				if(after_func != NULL) {
						after_func++;
						
						char search[] = "{";
						char *brack = strstr(after_func, search);
						if(brack != NULL) {
							char *function_name = strtok(after_func, "{");
							FILE *func = fopen("a.asm", "a");
							function_name[strlen(function_name)-1] = '\0';
							fprintf(func, "\n%s:\n", function_name);
							fclose(func);

							FILE *read = fopen(fname, "r+");
							char line6[256];
							int line_better = 0;
							int line_line = lineline_num;

							int ifnum = 0;
							bool is_in_if = false;
							int ifnum_ln = 0;

							int callnum = 0;

							while(fgets(line6, sizeof(line6), read) != NULL) {
								/*char search_for_func[] = function_name;
								char func = strstr(line6, search_for_func);
								if(func != NULL) {
									
								}*/
								comment_check = __check_com__(line6);
								if(comment_check == true) {
									continue;
								}
								if(line_better != line_line) {
									line_better++;
								} else if(line_better == line_line) {
									line_better++;
									line_line++;
									char *end = strstr(line6, "}");
									char *main = strstr(line6, "func:main");
									if(end != NULL) {
										if(INFO_DEBUG == true){wlog_info(fname, line_better, "line:%d is the end of a function\n", line_better);}
										break;
									} else if(main != NULL) {
										if(INFO_DEBUG == true){log_info(fname, line_better, "line:%d found main function\n", line_better);}
										break;
									} else if(end == NULL && main == NULL){
										FILE *out;
										char *iffind = strstr(line6, "~if");
										if(iffind != NULL) {
											ifnum++;
											ifnum_ln = line_better;
											FILE *if_ = fopen(fname, "r+");
											is_in_if = IS_IN_IF(if_, line_better, fname);
										}
										char *callfind = strstr(line6, "call~");
										if(callfind != NULL) {callnum++;}
										asm_interp_func_funcs(line6,
															  out,
															  line_better,
															  ifnum_ln,
															  fname,
															  function_name,
															  ifnum,
															  callnum,
															  is_in_if);
									}
								}
							}	
						} else if(brack == NULL) {
							wlog_warn(fname, lineline_num, "sub function brackets not implimented yet\n\n");
						}

				} else if(after_func == NULL) {
						wlog_error(fname, lineline_num, "Function does not have delimiter ':'\n");
						continue;
				}
		} else if(func != NULL && main != NULL) {
			if(INFO_DEBUG == true){wlog_info(fname, lineline_num, "found main fuction");}
      			FILE *outputfunc = fopen("a.asm", "a");
	                fprintf(outputfunc, "\n\nglobal main\n\nmain:\n\t");
 	                fclose(outputfunc);

			FILE *main_func = fopen(fname, "r+");
			char mainline[256];
			int mainline_num = 0;
			int line_line = line_num;
			while(fgets(mainline, sizeof(mainline), main_func) != NULL) {
				comment_check = __check_com__(mainline);
				if(comment_check == true) {
					continue;
				}
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

						int ifnum = 0;
						bool is_in_if = false;
						int ifnum_ln = 0;

						int callnum = 0;

						while(fgets(lineline, sizeof(lineline), main_run) != NULL) {

							/*if(ifscope == there) {
								char *b = strstr(lineline, "end");
								if(b != NULL) {
									ifscope = NULL;
								}
								continue;
							}*/

							comment_check = __check_com__(lineline);
							if(comment_check == true) {
								continue;
							}

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
									char *iffind = strstr(lineline, "~if");
									if(iffind != NULL) {
										ifnum++;
										ifnum_ln = line_yo;
										FILE *if_ = fopen(fname, "r+");
										is_in_if = IS_IN_IF(if_, line_yo, fname);
									}
									char *callfind = strstr(lineline, "call~");
									if(callfind != NULL) {callnum++;}
									asm_interp_func_funcs(lineline,
														  out,
														  line_yo,
														  ifnum_ln,
														  fname,
														  "main",
														  ifnum,
														  callnum,
														  is_in_if);
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

	/*fclose(file);*/
	/*fclose(output);*/
	return 0;

}

void compile(int argc, char *argv[]) {

	struct ArgparseParser parser = argparse_init("wesm", argc, argv);

	argparse_add_option(&parser, "--output", "-o", ARGPARSE_FLAG);
	argparse_add_option(&parser, "--assembly", "-a", ARGPARSE_FLAG); /* keeps the tmp assembly file*/
   	argparse_add_option(&parser, "--gcc", "-cc", ARGPARSE_FLAG); /* ex: wesm main.well -cc ::-lpthread -lcurl -g:: -o main*/
	argparse_add_option(&parser, "--info", "-i", ARGPARSE_FLAG);


	const char *out;
	bool keep_asm;

	const char *gcc_options;

	#if defined _WIN32 | defined _WIN64 | defined __WIN32__
	        const char *start = "nasm -f win64 a.asm -o a.o";
			    const char *linker = "gcc a.o -no-pie";
	#else
	        const char *start = "nasm -f elf64 a.asm -o a.o";
	        const char *linker = "gcc a.o -no-pie";
	#endif

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

	/*-cc is meant to be the last arg used*/

	if(argparse_option_exists(parser, "--gcc") != ARGPARSE_NOT_FOUND ||
			argparse_option_exists(parser, "-cc") != ARGPARSE_NOT_FOUND) {
		int i = 1;
		for(i = 1; i < 256; i++) {
			if(argv[i] == NULL) {
				break;
			}
			if(!strcmp(argv[i], "-gcc") || !strcmp(argv[i], "-cc")) {
				/*gcc_options = argv[i + 1];
				char *tmp = strstr(gcc_options, "::");*/
				char buf[0x100];
				int j;
				for(j = i+1; j >= i+1; j++) {
					if(argv[j] == NULL) {
						break;
					}

					char *outarg = strstr(argv[j], "-o");
					char *outarg_full = strstr(argv[j], "--output");
					if(outarg != NULL || outarg_full != NULL) {
						continue;
					}
					char *wellfile = strstr(argv[j], ".well");
					if(wellfile != NULL) {
						continue;
					}
					snprintf(buf, sizeof(buf), "%s %s", buf, argv[j]);
				}
				snprintf(gcc_buf, sizeof(gcc_buf), "%s", buf);
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

	if(gcc_buf != NULL) {
		snprintf(final_buf, sizeof(final_buf), "%s && %s %s %s", start, linker, gcc_buf, out_buf);
	} else {
		snprintf(final_buf, sizeof(final_buf), "%s && %s %s", start, linker, out_buf);
	}
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
#if defined _WIN32 | defined _WIN64 | defined __WIN32__
    system("del a.asm");
    system("del a.o");
#else
    system("rm -f a.asm a.o");
#endif
	} else {
#if defined _WIN32 | defined _WIN64 | defined __WIN32__
    system("del a.o");
#else
		system("rm -f a.o");
#endif
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

	/* [ TEST ] 
	asm2obj("./test/test.asm", "~win", "~x32");
	parser("./test/test.asm", "./test/test.o");
	return 0;
	 [ END TEST ] */

	if(argv[1] == NULL) {
		log_error("\n:: Invalid file name, ex: wesm (.well file) -o (.o file) (executable name)\n > wesm test.well -o test.o test\n\n");
		return 0;
	}

	compile(argc, argv);
	return 0;	

}
