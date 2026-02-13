//case function for division operator in the switch statement for binary expressions
// throws an runtime error instead of returning infinity/-infinity/NaN when division by zero is attempted

case SLASH:
    checkNumberOperands(expr.operator, left, right);

    double divisor = (double) right;
    if (divisor == 0) {
        throw new RuntimeError(expr.operator, "Division by zero.");
    }

    return (double) left / divisor;