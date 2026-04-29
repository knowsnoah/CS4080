//Chapter 24 Challenge Question 2

//in vm.c file 
  case OBJ_NATIVE: {
    ObjNative* native = AS_NATIVE_OBJ(callee);

    if (argCount != native->arity) {
      runtimeError("Expected %d arguments but got %d.", native->arity, argCount);
      return false;
    }
  }


  //one change in object.h
  typedef struct {
    Obj obj;
    NatvieFn function;
    int arity;
  } ObjNative;

  //native functions previously didnt check argument count
  // could lead to reading invalid or uninitialized memory
  // added an airty field to native functions
  // checked argCount before calling the function