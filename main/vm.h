#ifndef VM_H
#define VM_H

#include <stdbool.h>

// Simple stack-based VM on ThingBot (ESP32C3)
typedef struct
{
    const int *prog;
    int ip;
    int sp;
    int stack[256];
    bool running;
} VM;

void vm_init(VM *vm, const int *prog);
int vm_fetch(VM *vm);
void vm_exec(VM *vm, int opcode);
void vm_run(VM *vm);

#endif // VM_H