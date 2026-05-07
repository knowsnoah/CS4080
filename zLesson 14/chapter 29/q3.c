//challenge 29 challenge question 3

struct ObjClass:
typedef struct {
    Obj obj;
    ObjFunction* function;
    ObjUpvalue** upvalues;
    int upvalueCount;
    struct ObjClass* owner; //new field for superclass

} ObjClass

typedef struct ObjClass {
    Obj obj;
    ObjString* name;
    Table methods;
    Table ownMethods; //new field for own methods
    struct ObjClass* superclass; //new field for superclass
}


static void inner_(bool canAssign) {
    (void)canAssign;
    if (currentClass == NULL) || 
        (current->type != TYPE_METHOD && current->type != TYPE_INITIALZIER) {
            error("Can't use 'inner' outside of a method");
            return;
        }

    consume(TOKEN_LEFT_PAREN, "Expect '(' after 'inner'.");
    emitByte(OP_GET_LOCAL, 0);
    uint8_t argCount = argumentList();

    ObjString* name = current->function->name;
    uint8_t argCount = argumentList();

    ObjString* name = current->function->name;
    uint8_t method = makeConstant(OBJ_VALUE(name));
    emitBytes(OP_INVOKE, method);
    emitByte(argCount);
}

