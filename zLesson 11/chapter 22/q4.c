//Chapter 22 Challenge Question 4

//compiler.c (local storage + larger slot support)
#define LOCALS_MAX 65536
Local locals[LOCALS_MAX];

typedef struct Compiler {
    struct Complier* enclosing;
    ObjFunction* function;
    FunctionType type;
    Local locals[LOCALS_MAX];
    int localCount;
    Upvalue upvalues[UINT8_COUNT];
    itn scopeDepth;    
} Compiler;

static void addLocal(Token name) {
    if (current->localCount == LOCALS_MAX) {
        error("Too many local variables in function.");
        return;
    }

    Local* local = &current->locals[current->localCount++];
    local->name = name;
    local->depth = -1;
    local->isCaptured = false;
}
//----
static void emitShort(uint16_t value){
    emitByte((value >> 8) & 0xff);
    emitByte(value & 0xff);
}

static void emitLocalInstruction(uint8_t short0p, uint8-t long0p, int slot){
    if (slot <= UINT8_MAX) {
        emitBytes(short0p, (uint8_t)slot);
    } else if (slot <= UINT16_MAX) {
        emitByte(long0p);
        emitShort((uint16_t)slot);
    } else {
        error("Too many variables in function.");
    }
}


//Resolve variable --> decides if its local or global
static void namedVariable(Token name, bool canAssign) {
    int arg = resolveLocal(current, &name);

    if (canAssign && match(TOKEN_EQUAL)){
        expression();

        if (arg != -1) {
            emitLocalInstruction(OP_SET_LOCAL, OP_SET_LOCAL_LONG, arg);
        } else if ((arg = resolveUpvalue(current, &name)) != -1) {
            emitBytes(OP_SET_UPVALUE, (uint8_t)arg);
        } else {
            arg = identifierConstant(&name);
            emitBytes(OP_SET_GLOBAL, (uint8_t)arg);
        }
    } else {
        if (arg != -1) {
            emitLocalInstruction(OP_GET_LOCAL, OP_SET_LOCAL_LONG, arg);
        } else if ((arg = resolveUpvalue(current, &name)) != -1){
            emitBytes(OP_SET_UPVALUE, (uint8_t)arg);
        } else {
            arg = identifierConstant(&name);
            emitBytes(OP_GET_GLOBAL, (uint8_t)arg);
        }
    }
}


///emits correct bytecode instruction
emitBytes(get0p, (uint8_t)arg);

//storeslocl variable info (name, depth, isCaptured)
typedef struct {
    Token name;
    int depth;
    bool isCaptured;
} Local;

//prevents too many local variable 
if (current->localCount == LOCALS_MAX) {
    error("Too many local variables in function.");
    return;
}


//bytecode + vm changes
//in chunk.h
OP_Method, 
OP_GET_LOCAL_LONG,
OP_SET_LOCAL_LONG, //methods and initializers method-op

//in vm.c reads 2-byte slot index (bigger range)
#define READ_SLOT_LONG() \
    (uint16_t)((READ_BYTE() << 8) | READ_BYTE())

//loads local from stack using slot index
case OP_GET_LOCAL: {
    uint8_t slot = RWAD_BYTE();
    case OP_GET_LOCAL_LONG: {
        uint16_t slot = READ_SLOT_LONG();
        push(frame->slots[slot]);
        break;
}

//updates local value withohut popping
case OP_SET_LOCAL: {
    uint8_t slot = READ_BYTE();
    case OP_SET_LOCAL_LONG: {
        uint16_t slot = READ_SLOT_LONG();
        frame->slots[slot] = peek(0);
        break;
    }
}


//debug / disassembler changes
//in debug.c
static int shortInstruction(const char* name, Chunk* chunk, int offest) {
    uint16-t slot = (uint16_t)(chunk->code[offset = 1] << 8);
    slot |= chunk->code[offset + 2];
    printf("%-16s %4d\n", name, slot);
    return offset + 3;
}

case OP_GET_LOCAL:
    return byteInstruction("OP_GET_LOCAL_LONG", chunk, offset);
case OP_SET_LOCAL:
    return byteInstruction("OP_SET_LOCAL_LONG", chunk, offset);
case OP_GET_LOCAL_LONG:
    return shortInstruction("OP_GET_LOCAL_LONG", chunk, offset);    
case OP_SET_LOCAL_LONG:
    return shortInstruction("OP_SET_LOCAL_LONG", chunk, offset);
