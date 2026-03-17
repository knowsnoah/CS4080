//Chapter 15 Virtual Machine
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

//global vm variable
VM vm;

static void resetStack() {
    vm.stackTop = vm.stack;
}

//CHANGES FOR QUESTION 3
void initVM() {
    vm.stackCapacity = 256;
    vm.stack = malloc(sizeof(Value) * vm.stackCapacity);
    resetStack();
}

//CHANGES FOR QUESTION 3
void freeVM() {
    free(vm.stack);
}

//CHANGES FOR QUESTION 3
void push(Value value) {

    if (vm.stackTop - vm.stack >= vm.stackCapacity) {
        vm.stackCapacity *= 2;
        vm.stack = realloc(vm.stack, sizeof(Value) * vm.stackCapacity);
        vm.stackTop = vm.stack + vm.stackCapacity / 2;
    }

    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
//CHANGES FOR QUESTION 4
#define BINARY_OP(op) \
do { \
vm.stackTop[-2] = vm.stackTop[-2] op vm.stackTop[-1]; \
vm.stackTop--; \
} while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_ADD:      BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE:   BINARY_OP(/); break;
                //CHANGES FOR QUESTION 4
            case OP_NEGATE:
                vm.stackTop[-1] = -vm.stackTop[-1];
                break;
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}