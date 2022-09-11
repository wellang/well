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

int asm_interp_var_funcs(char line[], FILE *out, int line_num, const char *fname) {
 
        string_interp(line, out);
        length_interp(line, out);
        int_interp(line, out);

        char_interp(out, line);
        print_asm_interp(out, line, line_num, fname);
 
        return 0;

}

int asm_interp_func_funcs(char line[], FILE *out, int line_num, const char *fname) {

        mov_interp(line, out, line_num, fname);
        push_interp(line, out);

        syscall_interp(line, out);
        pop_interp(out, line, line_num, fname);
        array_run(out, line);
        cif_interp(out, line, line_num, fname);
        halt_interp(out, line, line_num, fname);
        bits_interp(out, line, line_num, fname);
 //     run_interp(out, line);
        print_asm_interp(out, line, line_num, fname);
        lea_interp(line, out, line_num);
        call_interp(out, line, line_num, fname);
        return0(out, line, line_num, fname);
 
        return 0;

}
