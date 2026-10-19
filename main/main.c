#include <stdio.h>
#include "opcode.h"
#include "vm.h"

void app_main(void)
{
    const int prog[] = {
        PSH, 10,            // x = 10
        PUT_LOCL, 0,        // local[0] = x
        GET_LOCL, 0,        // copy x from local[0] to stack
        PSH, 1000,          
        GT,                 // compare b (1000) with a (x)
        JNZ, 20,            // if not zero, jump to halt
        GET_LOCL, 0,        // GT consume x, so get x again
        PSH, 5,             
        MUL,                // x * 5
        PUT_LOCL, 0,        // pop the value of stack into local[0]
        JMP, 4,             // jump to prog[4]
        HLT
    };

    VM vm;
    vm_init(&vm, prog);
    vm_run(&vm);
}
