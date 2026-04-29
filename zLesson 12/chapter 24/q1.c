//Chapter 24 Challenge Question 1

//in vm.c file
static InterpretResult run() {
    CallFrame* frame = &vm.frames[vm.frameCount - 1];
    register uint8_t* ip = frame->ip;

#define READ_BYTE() (*ip++)
#define READ_SHORT() \
    (ip += 2, (uint16_t)((ip[-2] << 8) | ip[-1]))
}
    
        frame->ip = ip;
        if(!callValue(peek(argCount), argCount)) {
            return INTERPRET_RUNTIME_ERROR;
        }
        frame = &vm.frames[vm.frameCount - 1];
        ip = frame->ip;

//ip is accessed every instruction int he VM loop
//stored in ip (a local variable) to reduce pointer access 
//requires saving/restoring when switching frames
//small performance improvement in tight loops