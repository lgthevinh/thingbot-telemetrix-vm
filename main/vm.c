#include <stdio.h>
#include "esp_log.h"
#include "vm.h"
#include "opcode.h"

static const char *TAG = "vm";

static int vm_fetch(VM *vm);
static void vm_exec(VM *vm, int opcode);

void vm_init(VM *vm, const int *prog)
{
    vm->prog = prog;
    vm->ip = 0;
    vm->sp = -1;
    vm->running = true;
}

void vm_run(VM *vm)
{
    while (vm->running)
    {
        int op_code = vm_fetch(vm);
        vm_exec(vm, op_code);
    }
}

static int vm_fetch(VM *vm)
{
    return vm->prog[vm->ip++];
}

static bool vm_check_local(VM *vm, int idx)
{
    if (idx >= 0 && idx < VM_LOCALS)
    {
        return true;
    }

    ESP_LOGE(TAG, "bad local idx %d, ip %d", idx, vm->ip - 2);
    vm->running = false;
    return false;
}

static void vm_exec(VM *vm, int opcode)
{
    switch (opcode)
    {
    case HLT:
        vm->running = false;

        ESP_LOGI(TAG, "halt, ip %d", vm->ip - 1);
        break;

    case PSH:
    {
        int val = vm_fetch(vm);
        vm->stack[++vm->sp] = val;

        ESP_LOGD(TAG, "psh %d, ip %d, sp %d", val, vm->ip - 2, vm->sp);
        break;
    }

    case ADD:
    {
        int b = vm->stack[vm->sp--];
        int a = vm->stack[vm->sp--];
        vm->stack[++vm->sp] = a + b;

        ESP_LOGD(TAG, "add %d + %d = %d, ip %d, sp %d", a, b, a + b, vm->ip - 1, vm->sp);
        break;
    }

    case MUL:
    {
        int b = vm->stack[vm->sp--];
        int a = vm->stack[vm->sp--];
        vm->stack[++vm->sp] = a * b;

        ESP_LOGD(TAG, "mul %d * %d = %d, ip %d, sp %d", a, b, a * b, vm->ip - 1, vm->sp);
        break;
    }

    case SUB:
    {
        int b = vm->stack[vm->sp--];
        int a = vm->stack[vm->sp--];
        vm->stack[++vm->sp] = a - b;

        ESP_LOGD(TAG, "sub %d - %d = %d, ip %d, sp %d", a, b, a - b, vm->ip - 1, vm->sp);
        break;
    }

    case PUT_LOCL:
    {
        int idx = vm_fetch(vm);
        if (!vm_check_local(vm, idx))
        {
            break;
        }
        vm->local[idx] = vm->stack[vm->sp--];

        ESP_LOGD(TAG, "put_loc [%d] = %d, ip %d, sp %d", idx, vm->local[idx], vm->ip - 2, vm->sp);
        break;
    }

    case GET_LOCL:
    {
        int idx = vm_fetch(vm);
        if (!vm_check_local(vm, idx))
        {
            break;
        }
        vm->stack[++vm->sp] = vm->local[idx];

        ESP_LOGD(TAG, "get_loc [%d] = %d, ip %d, sp %d", idx, vm->local[idx], vm->ip - 2, vm->sp);
        break;
    }

    case JMP:
    {
        int ip = vm->stack[vm->sp--];

        ESP_LOGD(TAG, "jmp %d -> %d, sp %d", vm->ip - 1, ip, vm->sp);
        vm->ip = ip;
        break;
    }

    default:
        ESP_LOGE(TAG, "bad opcode %d, ip %d", opcode, vm->ip - 1);
        vm->running = false;
        break;
    }
}
