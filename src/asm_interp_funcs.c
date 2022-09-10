 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
  
 #include "mov_search.h"
 #include "syscall_interp.h"
 #include "push_search.h"
 #include "types.h"
 #include "log.h"
 #include "instructions.h"
 #include "asm_macros.h"
 #include "lea.h"

int asm_interp_var_funcs(char line[], FILE *out) {
 
        string_interp(line, out);
        length_interp(line, out);
        int_interp(line, out);

        char_interp(out, line);
        print_asm_interp(out, line);
 
        return 0;

}

int asm_interp_func_funcs(char line[], FILE *out, int line_num) {

        mov_interp(line, out);
        push_interp(line, out);

        syscall_interp(line, out);
        pop_interp(out, line);
        array_run(out, line);
        cif_interp(out, line);
        halt_interp(out, line);
        bits_interp(out, line);
 //       run_interp(out, line);
        print_asm_interp(out, line);
        lea_interp(line, out, line_num);
 	call_interp(out, line);
 	return0(out, line);
 
        return 0;

}
