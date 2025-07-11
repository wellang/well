/*Copyright (c) 2024 Tristan Wellman*/
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
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
	if(CPU==AMD_X86_64) {
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
	} else if(CPU==I386) {
    	switch(regNum) {
        	case RDI: return "edi";
        	case RSI: return "esi";
        	case RDX: return "edx";
        	case RCX: return "ecx";
        	case R8_: return "r8";
        	case R9_: return "r9";
        	case RAX: return "eax";
        	case XMM0: return "xmm0";
        	case AMD64SP: return "sp";
    	};
	}
    return NULL;
}

/*
 * Instruction Conversion
 * This x86_64 version checks for 32-bit and will change registers accordingly.
 * */

char *convertInstructionAMD_X86_64(AsmOut *out, Instruction ins) {
	char outBuf[2048] = {0};

	/*
	 * Move: move~ r1, r2
	 * */
	if(!strcmp(ins.instruction, "move")) {
		char *val1 = NULL;
		char *val2 = NULL;
		if(checkRegister(ins.arguments[0])) {
			char *ARMReg = mapRegisterAMD_X86_64(ins.arguments[0]);
			val1 = calloc(strlen(ARMReg)+128, sizeof(char));
			strcpy(val1, ARMReg);
		} else {
			Variable v = getVarFrom(out->parser, ins.arguments[0]);
			char asmVName[1024];
			switch(v.type) {
				case STRING: sprintf(asmVName, "wl_str_%s", ins.arguments[0]);break;
				case CHAR: sprintf(asmVName, "wl_ch_%s", ins.arguments[0]);break;
				case INT: sprintf(asmVName, "wl_int_%s", ins.arguments[0]);break;
				case FLOAT: sprintf(asmVName, "wl_fl_%s", ins.arguments[0]);break;
				case VOID: /*TODO*/break;
			};
			val1 = calloc(strlen(asmVName)+128, sizeof(char));
			strcpy(val1, asmVName);
		}
		if(checkRegister(ins.arguments[1])) {
			char *ARMReg = mapRegisterAMD_X86_64(ins.arguments[1]);
			val2 = calloc(strlen(ARMReg)+128, sizeof(char));
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
			val2 = calloc(strlen(asmVName)+128, sizeof(char));
			strcpy(val2, asmVName);
		}
		char *mov = "movq";
		if(!ISREG(val1)) strcat(val1, "(%rip)");
		else STARTAPPCHAR(val1, '%');
		if(!ISREG(val2)) strcat(val2, "(%rip)");
		else STARTAPPCHAR(val2, '%');
		if(CPU==AMD_X86_64) {
			snprintf(outBuf, sizeof(outBuf),
					"\t%s %s,%s\n", mov, val1, val2);
		} else if(CPU==I386) {
			snprintf(outBuf, sizeof(outBuf),
					"\tmovl %s,%s\n", val1, val2);
		}
		if(val1!=NULL) free(val1);
		if(val2!=NULL) free(val2);
	/*
	 * Call: call~ printf
	 * */
	} else if(!strcmp(ins.instruction, "call")) {
        if(ins.argLen>0 && ins.arguments[0]!=NULL)
            snprintf(outBuf, sizeof(outBuf), "\tcall %s\n", ins.arguments[0]);
	/*
	 * Return: return~ 0
	 * */
	} else if(!strcmp(ins.instruction, "return")) {
		if(ins.arguments[0]!=NULL) {
			if(strlen(ins.arguments[0])==0) ins.arguments[0] = "0";
			char *dealloc = stackDeallocateAMD_X86_64();
			snprintf(outBuf, sizeof(outBuf), "\tmovl $%s, %%eax\n%s\tret\n",
					ins.arguments[0], dealloc);
			free(dealloc);
		}
    
	/*
	 * Bitwise Instructions (Logical modifications are made with symbol operators)
	 * */

	/* NOT: not~ r1, r2
	 * r1 = ~r2
	 * */
	} else if(!strcmp(ins.instruction, "not")) {
		if(ins.arguments[0]!=NULL&&ins.arguments[1]!=NULL) {
			char *dest = mapRegisterAMD_X86_64(ins.arguments[0]);
			char *src = mapRegisterAMD_X86_64(ins.arguments[1]);
			if(!strcmp(src,dest)) {
				if(CPU==AMD_X86_64) 
					snprintf(outBuf, sizeof(outBuf), "\tnotq %%%s\n", dest);
				else if(CPU==I386) 
					snprintf(outBuf, sizeof(outBuf), "\tnotl %%%s\n", dest);
			} else {
				if(CPU==AMD_X86_64) {
					snprintf(outBuf, sizeof(outBuf), "\tmovq %%%s, %%%s\n\tnotq %%%s\n",
							src, dest, dest);
				} else if(CPU==I386) {
					snprintf(outBuf, sizeof(outBuf), "\tmovl %%%s, %%%s\n\tnotl %%%s\n",
							src, dest, dest);
				}
			}
		} 
	
	/* AND: and~ r1, r2, r3
	 * r1 = r2&r3
	 * */
	} else if(!strcmp(ins.instruction, "and")) {
		if(ins.arguments[0]!=NULL&&ins.arguments[1]!=NULL&&
				ins.arguments[2]!=NULL) {
			char *dest = mapRegisterAMD_X86_64(ins.arguments[0]);
			char *s1 = mapRegisterAMD_X86_64(ins.arguments[1]);
			char *s2 = mapRegisterAMD_X86_64(ins.arguments[2]);
			if((!strcmp(dest,s1)&&!strcmp(dest,s2))||!strcmp(s1,s2)) {
				/*If the are the same it's always 1*/
				snprintf(outBuf, sizeof(outBuf), "\tmovl $1, %%%s\n", dest);
			} else {
				if(CPU==AMD_X86_64) {
					snprintf(outBuf, sizeof(outBuf), "\tmovq %%%s, %%%s\n\tandq %%%s, %%%s\n",
							s1, dest, s2, dest);
				} else if(CPU==I386) {
					snprintf(outBuf, sizeof(outBuf), "\tmovl %%%s, %%%s\n\tandl %%%s, %%%s\n",
							s1, dest, s2, dest);

				}
			} 
		}
	
	/* OR: or~ r1, r2, r3
	 * r1 = r2|r3
	 * */
	} else if(!strcmp(ins.instruction, "or")) {
		if(ins.arguments[0]!=NULL&&ins.arguments[1]!=NULL&&
				ins.arguments[2]!=NULL) {
			char *dest = mapRegisterAMD_X86_64(ins.arguments[0]);
			char *s1 = mapRegisterAMD_X86_64(ins.arguments[1]);
			char *s2 = mapRegisterAMD_X86_64(ins.arguments[2]);
			if((!strcmp(dest,s1)&&!strcmp(dest,s2))||!strcmp(s1,s2)) {
				/*If the are the same it's always 1*/
				if(CPU==AMD_X86_64) snprintf(outBuf, sizeof(outBuf), "\tmovq $1, %%%s\n", dest);
				else if(CPU==I386) snprintf(outBuf, sizeof(outBuf), "\tmovl $1, %%%s\n", dest);
			} else {
				if(CPU==AMD_X86_64) {
					snprintf(outBuf, sizeof(outBuf), "\tmovq %%%s, %%%s\n\torq %%%s, %%%s\n",
							s1, dest, s2, dest);
				} else if(CPU==I386) {
					snprintf(outBuf, sizeof(outBuf), "\tmovl %%%s, %%%s\n\torl %%%s, %%%s\n",
							s1, dest, s2, dest);
				}
			} 
		}
	
	/* NOR: nor~ r1, r2, r3
	 * r1 = !(r2|r3)
	 * */
	} else if(!strcmp(ins.instruction, "nor")) {
		if(ins.arguments[0]!=NULL&&ins.arguments[1]!=NULL&&
				ins.arguments[2]!=NULL) {
			char *dest = mapRegisterAMD_X86_64(ins.arguments[0]);
			char *s1 = mapRegisterAMD_X86_64(ins.arguments[1]);
			char *s2 = mapRegisterAMD_X86_64(ins.arguments[2]);
			if((!strcmp(dest,s1)&&!strcmp(dest,s2))||!strcmp(s1,s2)) {
				/*If the are the same it's always 0*/
				if(CPU==AMD_X86_64) snprintf(outBuf, sizeof(outBuf), "\tmovq $0, %%%s\n", dest);
				else if(CPU==I386) snprintf(outBuf, sizeof(outBuf), "\tmovl $0, %%%s\n", dest);
			} else {
				if(CPU==AMD_X86_64) {
					snprintf(outBuf, sizeof(outBuf), 
							"\tmovq %%%s, %%%s\n\torq %%%s, %%%s\n\tnotq %%%s\n",
							s1, dest, s2, dest, dest);
				} else if(CPU==I386) {
					snprintf(outBuf, sizeof(outBuf), 
							"\tmovl %%%s, %%%s\n\torl %%%s, %%%s\n\tnotl %%%s\n",
							s1, dest, s2, dest, dest);
				}
			} 
		}


	/* NAND: nand~ r1, r2, r3
	 * r1 = ~(r2&r3)
	 * */
	} else if(!strcmp(ins.instruction, "nand")) {
		if(ins.arguments[0]!=NULL&&ins.arguments[1]!=NULL&&
				ins.arguments[2]!=NULL) {
			char *dest = mapRegisterAMD_X86_64(ins.arguments[0]);
			char *s1 = mapRegisterAMD_X86_64(ins.arguments[1]);
			char *s2 = mapRegisterAMD_X86_64(ins.arguments[2]);
			if((!strcmp(dest,s1)&&!strcmp(dest,s2))||!strcmp(s1,s2)) {
				/*If the are the same it's always 0*/
				if(CPU==AMD_X86_64) snprintf(outBuf, sizeof(outBuf), "\tmovq $0, %%%s\n", dest);
				else if(CPU==I386) snprintf(outBuf, sizeof(outBuf), "\tmovl $0, %%%s\n", dest);
			} else {
				if(CPU==AMD_X86_64) {
					snprintf(outBuf, sizeof(outBuf), 
							"\tmovq %%%s, %%%s\n\tandq %%%s, %%%s\n\tnotq %%%s\n",
							s1, dest, s2, dest, dest);
				} else if(CPU==I386) {
					snprintf(outBuf, sizeof(outBuf), 
							"\tmovl %%%s, %%%s\n\tandl %%%s, %%%s\n\tnotq %%%s\n",
							s1, dest, s2, dest, dest);

				}
			} 
		}
	
	
	/* XOR: xor~ r1, r2, r3
	 * r1 = r2^r3
	 * */
	} else if(!strcmp(ins.instruction, "xor")) {

	}

	char *ret = calloc(strlen(outBuf)+1, sizeof(char));
    strcpy(ret, outBuf);
	return ret;
}
