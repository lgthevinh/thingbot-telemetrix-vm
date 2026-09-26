#include "vm.h"
#include "opcode.h"
#include <stdio.h>

void vm_init(VM *vm, int *prog) {
    vm->prog = prog;
    vm->ip = 0;
    vm->sp = -1;
    vm->running = true;
}

int vm_fetch(VM *vm) {
    return vm->prog[vm->ip++];
}

void vm_exec(VM *vm, int opcode) {
    switch (opcode)
    {
    case HLT:
        vm->running = false;
        break;
    
    default:
        break;
    }
}