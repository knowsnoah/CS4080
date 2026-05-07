//chapter 29 challenge question 1  

//instead of looking at a hash table, we cache the initializer directly
//in the ObjClass
typedef struct ObjClass {
    Obj obj;
    ObjString* name;
    Value initializer; //new field for caching the initializer
    Table methods;
} ObjClass;

//we make it nil when creating a new class
ObjClass* newClass(ObjString* name) {
    ObjClass* klass = ALLOCATE_OBJ(ObjClass, OBJ_CLASS);
    klass->name = name;
    klass->initalizer = NIL_VALUE; //initialize the initializer to nil
    initTable(&klass->methods);
    return klass;
}

//when we define methods, if it is initializer method, we store it in the initializer field.
static void defineMethod(ObjString* name) {
    Value method = peek(0);
    ObjClass* klass = AS_CLASS(peek(1));
    tableSet(&klass->methods, name, method);
    if (strcmp(name->chars, "init") == 0) {
        klass->initializer = method; //cache the initializer    
        pop();
}

//so when we are calling it, we call the initializer field
case OBJ_CLASS: {
    ObjClass* klass = AS_CLASS(callee);
    vm.stackTop[-argCount - 1] = OBJ_VAL(newInstance(klass));
    if (!IS_NIL(klass->initializer)) {
        return callValue(klass->initializer, argCount); //new
    } else if (argCount != 0) {
        runtimeError("Expected 0 arguments but got %d.", argCount);
        return false;
    }
}