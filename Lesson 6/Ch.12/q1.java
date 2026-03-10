//Chapter 12 Question 1
//Modifying Parser.java - recognizing class keyword inside a class body
List<Stmt.Fucntion> classMethods = new ArrayList<>();
while (!check(RIGHT_BRACE) && !isAtEnd()){
    if (match(FUN)) {
        classMethods.add(function("method"));
    } else {
        methods.add(function("method"));
    }
}
return new Stmt.Class(name, superclass, methods, classMethods);


//Modifying Stmt.java - AST node carries both lists
static class Class extends Stmt {
    Class(Token name, Expr.Variable superclass,
        List<Stmt.Function> methods, 
        List<Stmt.Function> classMethods) {...}
    final List<Stmt.Function> methods;
    final List<Stmt.Function> classMethods;   
}


//Modifying Lox.java - AST node carreis both lists
class LoxClass extends LoxInstance implements LoxCallable {...}

//Two constructors: one for real classes, one for metaclassses
//prviate: creates a metaclass 
private LoxClass(String, name, LoxClass superclass, 
        Map<String, LoxFunction> methods) {

    super(null); //metaclasses dont have a metaclass
    }

//Public: create a normal class auto genrates its metaclass
LoxClass(String name, LoxClass superclass, 
        Map<String, LoxFunction> methods.
        Map<String, LoxFunction> classMethods) {
    super(new LoxClass(name + " metaclass", superclass, classMethods));

}


//Changing the Interpreter.java (two changes)
//Building the classMethods map when visiting a class declaration
Map<String, LoxFunction> classMethods = new HashMap<>();
for (Stmt.Function method : stmt.classMethods) {
    LoxFunction function = new LoxFunction(method, environment, false);
    classMethods.put(method.name.lexme, function);
}

//Pass classMethods to the LoxClass constructor
LoxClass klass = new LoxClass(stmt.name.lexme,
    (LoxClass)superclass, methods, classMethods);

public Object visitFunctionExpr(Expr.Get expr){
    Object object = evaluate(expr.object);
    if (object instanceof LoxInstance) {
        return ((LoxInstance) object).get(expr.name);
    }
    throw new RuntimeError(...);
}


//Lastly, in Resolver.java resolve static methods (outside the this scope)
beginScope();
scopes.peek().put("this", true);

for (Stmt.Function method : stmt.methods) {... resolveFunction(...) }

endScope();

for (Stmt.Function method : stmt.classMethods) {
    resolveFunction(method, FunctionType.METHOD);
}

