#include <stdio.h>
#include "opcode.h"
#include "vm.h"

void app_main(void)
{
    const int prog[] = {
        PSH, 2,
        PSH, 3,
        ADD,
        PUT_LOCL, 0,
        PSH, 5,
        GET_LOCL, 0,
        SUB,
        HLT,
    };

    VM vm;
    vm_init(&vm, prog);
    vm_run(&vm);
}
