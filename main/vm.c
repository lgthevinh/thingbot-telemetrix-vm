#include <stdio.h>
#include "esp_log.h"
#include "vm.h"
#include "opcode.h"

static const char *TAG = "vm";

void vm_init(VM *vm, const int *prog)
{
    vm->prog = prog;
    vm->ip = 0;
    vm->sp = -1;
    vm->running = true;
}

int vm_fetch(VM *vm)
{
    return vm->prog[vm->ip++];
}

void vm_exec(VM *vm, int opcode)
{
    switch (opcode)
    {
    case HAL:
        vm->running = false;
        ESP_LOGI(TAG, "halt at ip %d", vm->ip - 1);
        break;

    default:
        ESP_LOGE(TAG, "bad opcode %d at ip %d", opcode, vm->ip - 1);
        vm->running = false;
        break;
    }
}

void vm_run(VM *vm)
{
    while (vm->running)
    {
        int op_code = vm_fetch(vm);
        vm_exec(vm, op_code);
    }
}