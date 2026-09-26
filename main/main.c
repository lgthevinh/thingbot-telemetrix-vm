#include <stdio.h>
#include "opcode.h"
#include "vm.h"

void app_main(void)
{
    const int prog = {
        HAL};

    VM vm;
    vm_init(&vm, &prog);
    vm_run(&vm);
}
