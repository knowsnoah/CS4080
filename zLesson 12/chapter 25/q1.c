//Challenge Question 1

//Change #1: Update OP_CLOSURE in run() --> so nested function
// declarations avoid creatingt closures when no upvalues exist.

ObjFunction* function = AS_FUNCTION(READ_CONSTANT());

//only create closure if needed
if (function->upvalueCOunt == 0 ) {
    push(OBJ_VAL(function));
    break;
}

ObjClosure* closure = newClosure(function);
push(OBJ_VAL(closure));


//CHANGE #2: Update callValue() -> so the VM can call both nornmal
//ObjFunction and functions and ObjClosure closures.
case OBJ_CLOSURE:
    return call(AS_CLOSURE(callee), argCount);

case OBJ_FUNCTION: {
    ObjFunction* function = AS_FUNCTION(callee);

    ObjClosure* temp = newClosure(function);

    return call(temp, argCount);
}

//CHANGE 3: Update interpret() --> so the top-level script ony creates
//a closure when the function actually nees captured variables.
if (function->upvalueCount == 0) {
    ObjClosure* closure = newClosure(fucntion);

    pop();
    push(OBJ_VAL(closure));
    call(closure, 0);
} else {
    call(newClosure(function), 0);
}