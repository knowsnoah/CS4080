//Chapter 11 Challenge Question 4
//Code Changes for Resolver.java

private final Stack<Integer> scopeNextIndex = new Stack<>();

private void beginScope() {
    scopes.push(new HashMap<String, Variable >());
    scopeNextIndex.push(0); //added: intialize index for the new scope
}

private void declare(Token name){
    if (scopes.isEmpty()) return;

    //added assign and increment the unique index for this scope
    int index = scopeNextIndex.peek();
    scopeNextIndex.set(scopeNextIndex.size() -1, index + 1);

    //edited: store the index inside the Variable metadata
    scopes.peek().put(name.lexme, new Variable(name, VariableState.DECLARED, index));
}

private void resolveLocal(Expr expr, Token name) {
    for (int i = scopes.size() - 1; i >= 0; i--) {
        Map<String, Variable> scope = scopes.get(i);
        if (scope.containsKey(name.lexme)) {
            Variable variable = scope.get(name.lexme);
            //edited: pass both depth and unique index to the interpreter
            interpreter.resolve(expr, scopes.size() - 1 - i, variable.index);
            return;
        }
    }
}


//Second, File: Environment.java
//added: fast indexed storage list
private final List<Object> slots = new ArrayList<>();

void define(String name, Object value) {
    values.put(name, value);
    slots.add(value);
}

Object getAtIndex(int distance, int index){
    return ancestor(distance).slots.get(index);
}


//Lastly, Modify the Interpreter.java
//Edited: Changed map to store {depth, index} array
private final Map<Expr, int[]> locals = new HashMap<>();

private Object lookUpVariable(Token name, Expr expr) {
    int[] location = locals.get(expr);
    if (location != null){
        return environment.getAtIndex(location[0], location[1]);
    } else{
        return globals.get(name); //fallback for gloabl variables
    }
}
