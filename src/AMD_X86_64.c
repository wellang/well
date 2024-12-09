/*Copyright (c) 2024 Tristan Wellman*/
#include "AMD_X86_64.h"

char *stackAllocateAMD_X86_64() {
	/*auto to 16*/
	char *ret = calloc(1024, sizeof(char));
	sprintf(ret, "\tpushq %%rbp\n\tmovq %%rsp, %%rbp\n\tsubq $16, %%rsp\n");
	return ret;
}

char *stackDeallocateAMD_X86_64() {
	/*auto to 16*/
	char *ret = calloc(1024, sizeof(char));
	sprintf(ret, "\taddq $16, %%rsp\n\tpopq %%rbp\n");
	return ret;
}

char *mapRegisterAMD_X86_64(char *reg) {
    int regNum = regToEnum(reg);
    switch(regNum) {
        case RDI: return "rdi";
        case RSI: return "rsi";
        case RDX: return "rdx";
        case RCX: return "rcx";
        case R8_: return "r8";
        case R9_: return "r9";
        case RAX: return "rax";
        case XMM0: return "xmm0";
        case AMD64SP: return "sp";
    };
    return "rdi";
}

/*
 * Instruction Conversion
 * */

char *convertInstructionAMD_X86_64(AsmOut *out, Instruction ins) {
	char outBuf[2048] = {0};

	/*
	 * Move
	 * */
	if(!strcmp(ins.instruction, "move")) {
		char *val1;
		char *val2;
		if(checkRegister(ins.arguments[0])) {
			char *ARMReg = mapRegisterAMD_X86_64(ins.arguments[0]);
			val1 = strdup(ARMReg);
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
			val1 = strdup(asmVName);
		}
		if(checkRegister(ins.arguments[1])) {
			char *ARMReg = mapRegisterAMD_X86_64(ins.arguments[1]);
			val2 = strdup(ARMReg);
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
			val2 = strdup(asmVName);
		}

		snprintf(outBuf, sizeof(outBuf),
				"\tmov %s(%%rip),%s\n",
				val1, val2);
	/*
	 * Call
	 * */
	} else if(!strcmp(ins.instruction, "call")) {
        if(ins.argLen>0 && ins.arguments[0]!=NULL)
            snprintf(outBuf, sizeof(outBuf), "\tcall %s\n", ins.arguments[0]);
	/*
	 * Return
	 * */
	} else if(!strcmp(ins.instruction, "return")) {
		if(ins.arguments[0]!=NULL) {
			if(strlen(ins.arguments[0])==0) ins.arguments[0] = "0";
			sprintf(outBuf, "\tmov $%s, %%eax\n%s\tret\n",
					ins.arguments[0], stackDeallocateAMD_X86_64());
		}
    }

	char *ret = calloc(strlen(outBuf)+1, sizeof(char));
    strcpy(ret, outBuf);
	return ret;
}
