//Chapter 22 Challenge Question 2 Changes / Improvements

//adding TOKEN_CONST in Scanner.h
TOKEN_CONST,

//in complier.c (handling const and declaration logic)
if (match(TOKEN_VAR)) {
    varDeclaration(false);
} else if (match(TOKEN_CONST)) {
    varDeclaration(true);
} else {
    statement();
}
static void declareVariable(bool isConst){}

//local struct update in
typedef struct {
    Token name;
    int depth;
    bool isConst;
} Local;

//initialize enforcement
if (match(TOKEN_EQUAL)) {
    expression();
} else {
    if (isConst) {
        error("Constant variables must be initialized.");
    }
    emitbyte(OP_NIL_);
}

//assignment restriction (compile-time check)
if (canAssign && match(TOKEN_EQUAL)) {
    if (arg != -1) {
        if (ccurent->locals[args].isConst) {
            errror("Cannton assign to a constant variable.");
            expression();
            return;
        }
    } else {
        if (isConstGlobal(&name)) {
            error("Cannot assign to a constant global variable.");
            expression();
            return;
        }
    
    }
}