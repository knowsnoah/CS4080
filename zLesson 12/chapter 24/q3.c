//challenge question #3

//in object.h
//changing the function signature so that native functions return
//a boolean to indicate success or failure, and use a result pointer 
//to store the actual return value.
typedef bool (*NativeFN)(int argCount, Value* args);

typedef struct {
    Obj obj;
    NativeFn function;
} ObjNative;


static bool sqrtNative(int argCount, Value* args, Value* result) {
    if (argCount != 1){
        runtimeError("Expected 1 argument but got %d.", argCount);
        return false;
    }

    if (!IS_NUMBER(args[0])) {
        runtimeError("Argument must be a number.");
        return false;
    }

    double x = AS_NUMBER(args[0]);
    if (x<0) {
        runtimeError("Cannot take square root of a negative number.");
        return false;
    }

    *result = NUMBER_VAL(sqrt(x));
    return true;
}


//in vm.c 
//in the VM, when calling the native function, we check if it returns
//false. If it does, we stop execution and report a runtime erro.
case OBJ_NATIVE: {
    ObjNative* native = AS_NATIVE(callee);
    Value result;
    if (!native->function(argCount, vm.stackTop - argCount, &result)) {
        runtimeError("Native function failed.");
        return false;
    }
    vm.stackTop -= argCount + 1; // pop callee and arguments
    push(result); // push the result of the native function
    return true;
  }

