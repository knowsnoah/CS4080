//function that overrides the visitBinaryExpr method to handle the binary expression evaluation

@Override
public Object visitBinaryExpr(Expr.Binary expr) {
    Object left = evaluate(expr.left);
    Object right = evaluate(expr.right);

    switch (expr.operator.type) {

        case PLUS:
            // Number + Number
            if (left instanceof Double && right instanceof Double) {
                return (double) left + (double) right;
            }

            // If either is a string → concatenate
            if (left instanceof String || right instanceof String) {
                return stringify(left) + stringify(right);
            }

            throw new RuntimeError(expr.operator,
                    "Operands must be two numbers or at least one string.");

        // other operators down here...

    }

    return null;
}