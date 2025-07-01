/*Copyright (c) 2024 Tristan Wellman*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "asmout.h"
#include "hexconvert.h"
#include "cpu.h"
#include "ARM_MAC.h"

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

char *mapRegister(char *reg) {
	int regNum = regToEnum(reg);	
	switch(regNum) {
		case X0: return "x0";
		case X1: return "x1";
		case X2: return "x2";
		case X3: return "x3";
		case X4: return "x4";
		case X5: return "x5";
		case X6: return "x6";
		case X7: return "x7";
		case MACARMSP: return "sp";
	};
	return "x0";
}

/*x registers are 64-bit w registers are 32*/
char *convertInstructionARM_MAC(AsmOut *out, Instruction ins) {
	/*
	 * This is just temporary so I can have something that works...
	 * */

	char outBuf[2048] = {0};

	/*
	 * Move
	 * */
	if(!strcmp(ins.instruction, "move")) {
		char *val1;
		char *val2;
		if(checkRegister(ins.arguments[0])) {
			char *ARMReg = mapRegister(ins.arguments[0]);
			val1 = calloc(strlen(ARMReg)+1, sizeof(char));
			strcpy(val1, ARMReg);
		} else {
			Variable v = getVarFrom(out->parser, ins.arguments[0]);
			char asmVName[1024];
			switch(v.type) {
				case STRING: sprintf(asmVName, "wl_str.%s", ins.arguments[0]);break;
				case CHAR: sprintf(asmVName, "wl_ch_%s", ins.arguments[0]);break;
				case INT: sprintf(asmVName, "wl_int_%s", ins.arguments[0]);break;
				case FLOAT: sprintf(asmVName, "wl_fl_%s", ins.arguments[0]);break;
				case VOID: /*TODO*/break;
			};
			val1 = calloc(strlen(asmVName)+1, sizeof(char));
			strcpy(val1, asmVName);
		}
		if(checkRegister(ins.arguments[1])) {
			char *ARMReg = mapRegister(ins.arguments[1]);
			val2 = calloc(strlen(ARMReg)+1, sizeof(char)); 
			strcpy(val2, ARMReg);
		} else {
			Variable v = getVarFrom(out->parser, ins.arguments[1]);
			char asmVName[1024];
			switch(v.type) {
				case STRING: sprintf(asmVName, "wl_str.%s", ins.arguments[1]);break;
				case CHAR: sprintf(asmVName, "wl_ch_%s", ins.arguments[1]);break;
				case INT: sprintf(asmVName, "wl_int_%s", ins.arguments[1]);break;
				case FLOAT: sprintf(asmVName, "wl_fl_%s", ins.arguments[1]);break;
				case VOID: /*TODO*/break;
			};
			val2 = calloc(strlen(asmVName)+1, sizeof(char));
			strcpy(val2, asmVName);
		}

		snprintf(outBuf, sizeof(outBuf), 
				"\tadrp %s,%s@PAGE\n\tadd %s, %s, %s@PAGEOFF\n",
				val2, val1, val2, val2, val1);
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

	/*
	 * SStruct - save structure from return.
	 * NOTE: this is sort of patch work so I can manage C lib structs easier
	 * */
	} else if(!strcmp(ins.instruction, "sstruct")) {
		char *reg = mapRegister(ins.arguments[0]);
		snprintf(outBuf, sizeof(outBuf), 
				"\tstr %s, [sp, #8]\n", reg);
	
	/*
	 * LStruct - Load returned C struct into register
	 * NOTE: this is sort of patch work so I can manage C lib structs easier
	 * */
	} else if(!strcmp(ins.instruction, "lstruct")) {
		char *reg = mapRegister(ins.arguments[0]);
		snprintf(outBuf, sizeof(outBuf), "\tldr %s, [sp, #8]\n", reg);

	/*
	 * Jump - Jump to or from function 
	 * NOTE: This is "temporary" until I get if statements and loops going
	 * */
	} else if(!strcmp(ins.instruction, "jump")) {
		snprintf(outBuf, sizeof(outBuf), "\tb _%s\n", ins.arguments[0]);
	
	/*
	 * Compare - comp two items and branch if zero
	 * NOTE: same as Jump
	 * */
	} else if(!strcmp(ins.instruction, "cmpz")) {
		char *arg1 = calloc(strlen(ins.arguments[0])+1, sizeof(char));
		strcpy(arg1, ins.arguments[0]);
		char *arg2 = calloc(strlen(ins.arguments[1])+1, sizeof(char));
		strcpy(arg2, ins.arguments[1]);
		char *arg3 = calloc(strlen(ins.arguments[2])+1, sizeof(char));
		strcpy(arg3, ins.arguments[2]);
		if(checkRegister(arg1)) arg1 = mapRegister(arg1);
		if(checkRegister(arg2)) arg2 = mapRegister(arg2);
		snprintf(outBuf, sizeof(outBuf), "\ttbz %s, %s, _%s\n", arg1, arg2, arg3);
	}

	char *ret = calloc(strlen(outBuf)+1, sizeof(char));
	strcpy(ret, outBuf);
	return ret;
}

