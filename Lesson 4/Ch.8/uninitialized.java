//Challenge Question #2
//In interpreter add this:

private static Object uninitialized = new Object();

//Then change the first line of visitVarStmt() to this:
Object value = uninitialized;

//Finally change the visitVariableExpr() method to this:

public Object visitVariableExpr(Expr.Variable expr) {
    Object value = environment.get(expr.name);
    if (value == uninitialized) {
        throw new RuntimeError(expr.name, 
            "Variable must be initialized before use."); 
    }
    return value;
}

