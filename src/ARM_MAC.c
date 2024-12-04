/*Copyright (c) 2024 Tristan Wellman*/

#include "parser.h"
#include "asmout.h"
#include "hexconvert.h"
#include "cpu.h"

/*These auto to 16 since we don't do local variables yet*/
char *stackAllocateARM_MAC() {
	/*auto to 16*/
	char *ret = calloc(1024, sizeof(char));
	sprintf(ret, "\tsub sp, sp, #16\n\tstp x29, x30, [sp, #0]\n\tadd x29, sp, #0\n");
	return ret; 
}

char *stackDeallocateARM_MAC() {
	/*auto to 16*/
	char *ret = calloc(1024, sizeof(char));
	sprintf(ret, "\tldp x29, x30, [sp, #0]\n\tadd sp, sp, #16\n");
	return ret; 
}

/*x registers are 64-bit w registers are 32*/
char *convertInstructionARM_MAC(AsmOut *out, Instruction ins) {
	/*
	 * This is just temporary so I can have something that works...
	 * */

	char outBuf[100] = {0};

	/*
	 * Move
	 * */
	if(!strcmp(ins.instruction, "move")) {
		/*TODO check instruction argument size for invalid args*/
		Variable v = getVarFrom(out->parser, ins.arguments[0]);
		char asmVName[1024];
		switch(v.type) {
			case STRING: sprintf(asmVName, "wl_str.%s", ins.arguments[0]);break;
			case CHAR: sprintf(asmVName, "wl_ch_%s", ins.arguments[0]);break;
			case INT: sprintf(asmVName, "wl_int_%s", ins.arguments[0]);break;
			case FLOAT: sprintf(asmVName, "wl_fl_%s", ins.arguments[0]);break;
			case VOID: /*TODO*/break;
		};
		snprintf(outBuf, sizeof(outBuf), 
				"\tadrp %s,%s@PAGE\n\tadd %s, %s, %s@PAGEOFF\n",
				"x0", asmVName, "x0", "x0", asmVName);
	/*
	 * Call
	 * */
	} else if(!strcmp(ins.instruction, "call")) {
        if(ins.argLen>0 && ins.arguments[0]!=NULL)
            snprintf(outBuf, sizeof(outBuf), "\tbl _%s\n", ins.arguments[0]);
	/*
	 * Return
	 * */
	} else if(!strcmp(ins.instruction, "return")) {
		if(ins.arguments[0]!=NULL) {
			if(strlen(ins.arguments[0])==0) ins.arguments[0] = "0";
			sprintf(outBuf, "\tmov x0, #%s\n%s\tret\n",
					ins.arguments[0], stackDeallocateARM_MAC());
		}
	}

	char *ret = strdup(outBuf);
	return ret;
}

