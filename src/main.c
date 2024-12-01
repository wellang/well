/*Copyright (c) 2024 Tristan Wellman*/
#include <time.h>
#include "util.h"
#include "wdata.h"
#include "parser.h"
#include "werror.h"
#include "asmout.h"
#include "cpu.h"

int argCheckOption(struct ArgparseParser *parser,
		char *option1, char *option2);

void runArgParsing(wData *data);

void initArgParseArgs(wData *data, int argc, char *argv[]); 

int main(int argc, char **argv) {

	clock_t start, end;
	start = clock();

	wData data;
	initArgParseArgs(&data, argc, argv);
	runArgParsing(&data);	

	WASSERT(data.main!=NULL,
			"FATAL:: No File provided");

	struct parserData *p = initParser(&data);
	parseProgram(p);

	AsmOut output;
	initAsmOut(p, &output);
	convertToAsm(&output);

	end = clock();
	char *cpu_str;
	GETCPUSTR(CPU, cpu_str);
	char timeBuf[100];
	snprintf(timeBuf, sizeof(timeBuf), "Compile time: %fs, %fms on %s", 
			((double)(end-start) / CLOCKS_PER_SEC), 
			(((double)(end-start) / CLOCKS_PER_SEC) * 1000), cpu_str);
	WLOG(INFO, timeBuf);

	WERROR_EXIT();

	freeAsm(&output);
	argparse_free(data.argParser);
	if(data.main!=NULL) fclose(data.main);

	return 0;
}

int argCheckOption(struct ArgparseParser *parser,
		char *option1, char *option2) {
	if(argparse_option_exists(*parser, option1)!=ARGPARSE_NOT_FOUND ||
			argparse_option_exists(*parser, option2)!=ARGPARSE_NOT_FOUND) return 1;
	return 0;
}

void runArgParsing(wData *data) {
	char *help = "WELLANG CLI HELP:\n\n"
    "--help      | -h: Need help? Use -h\n"
    "--output    | -o: Set name of executable output\n"
    "--gcc       | -cc: Set your cflags (ex: wesm main.well -cc '-g -lpthread')\n"
    "--assembly  | -a: Keep the assembly output file\n"
    "--info      | -i: Shows extra debug information at compile time\n\n"
    "--use-gnuld | -use-ld: Use gnu linker rather than gcc\n"
    "--ldflags   | -ldflags: Set your gnu linker flags (ex: wesm main.well -use-ld -ldflags '-T link.ld')\n";

	if(argCheckOption(&data->argParser, "--help", "-h")) {
		WLOG(INFO, help);
		exit(0);
	}
	if(argCheckOption(&data->argParser, "--info", "-i")) 
		data->USEINFO=1;
	if(argCheckOption(&data->argParser, "--assembly", "-a"))
		data->KEEPASM=1;


}

void initArgParseArgs(wData *data, int argc, char **argv) {
	data->argParser = argparse_init("well", argc, argv);
	data->KEEPASM=0;
	data->USEINFO=0;

	int i;
	for(i=0;i<argc;i++) {
		if(strstr(argv[i], ".well")) {
			data->main = fopen(argv[i], "r");
			WASSERT(data->main!=NULL,
					"FATAL:: Failed to open file: %s", argv[i]);
			data->fileName = argv[i];
			break;
		}
}

	WASSERT(&data->argParser!=NULL,
			"FATAL:: Failed to init argParse");


	argparse_add_argument(&data->argParser, "arg1");


	argparse_add_option(&data->argParser, "--help", "-h", ARGPARSE_FLAG);
	argparse_add_option(&data->argParser, "--output", "-o", ARGPARSE_FLAG);
	argparse_add_option(&data->argParser, "--gcc", "-cc", ARGPARSE_FLAG);
	argparse_add_option(&data->argParser, "--assembly", "-a", ARGPARSE_FLAG);
	argparse_add_option(&data->argParser, "--info", "-i", ARGPARSE_FLAG);
	argparse_add_option(&data->argParser, "--use-gnuld", "-use-ld", ARGPARSE_FLAG);
	argparse_add_option(&data->argParser, "--ldflags", "-ldflags", ARGPARSE_FLAG);
	
	argparse_error(data->argParser);
	
}

