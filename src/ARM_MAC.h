#ifndef ARM_MAC_H
#define ARM_MAC_H
#include "util.h"
#include "asmout.h"
#include "parser.h"

char *stackAllocateARM_MAC();
char *stackDeallocateARM_MAC();
char *convertInstructionARM_MAC(AsmOut *out, Instruction ins);

#endif
