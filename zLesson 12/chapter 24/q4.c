//Challenge Question 4

//we are adding this typeNative nativr function that returns
//the type of a value as a string. This allows us to inspect
//values at runtime and understand what the program is actually
//working with

//in vm.c

static bool typeNative(int argCount, Value* args, Value* result){
    if (argCount != 1) {
        runtimeError("Expected 1 argument but got %d.", argCount);
        return false;
    }

    Value value = args[0]; 

    if (IS_NUMBER(value)) {
        *result = OBJ_VAL(copyString("number", 6));
    } else if (IS_BOOL(value)) {
        *result = OBJ_VAL(copyString("bool", 4));
    } else if (IS_NIL(value)) {
        *result = OBJ_VAL(copyString("nil", 3));
    } else if (IS_STRING(value)) {
        *result = OBJ_VAL(copyString("string", 6));
    } else if (IS_FUNCTION(value)) {
        *result = OBJ_VAL(copyString("function", 8));
    } else if (IS_NATIVE(value)) {
        *result = OBJ_VAL(copyString("native", 6));
    } else {
        *result = OBJ_VAL(copyString("unknown", 7));
    }