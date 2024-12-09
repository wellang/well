/*Copyright (c) 2024 Tristan Wellman*/
#ifndef AMD_X86_64_H
#define AMD_X86_64_H
#include "util.h"
#include "asmout.h"
#include "parser.h"

enum registersAMD_X86_64 {
#if defined _WIN32 || defined _WIN64 || defined __WIN32__ || __CYGWIN__
  	RCX=0,
	RDX,
  	R8_,
  	R9_,
  	RDI,
  	RSI,
  	RAX,
  	XMM0,
  	AMD64SP
#else
    RDI=0,
    RSI,
    RDX,
    RCX,
    R8_,
    R9_,
    RAX, /*Return value*/
    XMM0,
    AMD64SP
#endif
};

char *stackAllocateAMD_X86_64();
char *stackDeallocateAMD_X86_64();
char *convertInstructionAMD_X86_64(AsmOut *out, Instruction ins);

#endif
