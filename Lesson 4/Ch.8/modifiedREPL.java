//Challenge Question #1
//There are three steps in order to modify the REPL 
//1. Add this to Parse.java:
Expr parseExpression() {
  try {
    Expr expr = expression();
    consume(TokenType.EOF, "Expect end of expression.");
    return expr;
  } catch (ParseError error) {
    return null;
  }
}

//2. Add this to Interpreter.java:
Object evaluateExpression(Expr expr) {
  return evaluate(expr);
}
//this is adding a public wrapper to evaluate the expression\


//3. Modify the REPL in Lox.java, inside the runprompt() method to look like this:
Scanner scanner = new Scanner(line);
List<Token> tokens = scanner.scanTokens();

Parser parser = new Parser(tokens);

//try parsing as expression first
Expr expr = parser.parseExpression();

if (expr != null && !hadError) {
  Object value = interpreter.evaluateExpression(expr);
  System.out.println(interpreter.stringify(value));
} else {
  hadError = false; // resetting error from expression attempt

  parser = new Parser(tokens);
  List<Stmt> statements = parser.parse();

  if (!hadError) {
    interpreter.interpret(statements);
  }
}

hadError = false;
