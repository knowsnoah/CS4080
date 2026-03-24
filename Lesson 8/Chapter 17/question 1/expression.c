#include <stdio.h>
#include <stdlib.h>
#include <string.h>

expression()
    calls parsePrecedence(PREC_ASSIGNMENT)

    CALL A: parsePrecedence(PREC_ASSIGNMENT)
        advance() consumes '('
        getRule(TOKEN_LEFT_PAREN) -> prefix = grouping
        calls grouping()

        grouping()
            calls expression() to parse inside the parentheses

            expression()
                calls parsePrecedence(PREC_ASSIGNMENT)

                CALL B: parsePrecedence(PREC_ASSIGNMENT)
                    advance() consumes '-'
                    getRule(TOKEN_MINUS) -> prefix = unary
                    calls unary()

                    unary()
                        operatorType - TOKEN_MINUS
                        calls parsePrecedence(PREC_UNARY) to pare the operand of unary '-'
                CALL C: parsePrecedence(PREC_UNARY)
                    advance() consumes '1'
                    getRule(TOKEN_NUMBER) -> prefix = number
                    calls number()

                    number()
                        emits constant 1

                    while PREC_UNARY <= precedence(current token '+')
                        compare PREC_UNARY <= PREC_TERM -> false
                    CALL C returns to unary()

                unary()
                    emits NEGATE
                returns to CALL B

            while PREC_ASSIGNMENT <= precedence(current token '+')
                compare PREC_ASSIGNMENT <= PREC_TERM -> true

                advance() consumes '+'
                getRule(TOKEN_PLUS) -> infix = binary
                calls binary()

binary()
    operatorType = TOKEN_PLUS
    getRule(TOKEN_PLUS) -> precedence = PREC_TERM
    calls parsePrecedence(PREC_TOKEN + 1)
    calls parsePrecedence(PREC_FACTOR) to parse right-hand side of '+'

    CALL D: parsePrecedence(PREC_FACTOR)
        advance() consumes '2'
        getRule(TOKEN_NUMBER) -> prefix = number
        calls number()

        number()
            emits constant 2

        while PREC_FACTOR <= precedence(current token ')')
            compare PREC_FACTOR <= PREC_NONE -> false
        CALL D returns to binary()

binary()
    emits ADD
    returns to CALL B

        while PREC_ASSIGNMENT <= precedence(current token ')')
            compare PREC_ASSIGNMENT <= PREC_NONE -> false
        CALL B returns to grouping()

    grouping()
        consume(TOKEN_RIGHT_PAREN) consumes ")"
    returns to CALL A

while PREC_ASSIGNMENT <= precedence(current token '*')
    compare PREC_ASSIGNMENT <= PREC_FACTOR -> true

    advance() consumes '*'
    getRule(TOKEN_STAR) -> infix = binary
    calls binary()

    binary()
        operatorType = TOKEN_STAR
        getRule(TOKEN_STAR) -> precedence = PREC_FACTOR
        calls parsePrecedence(PREC_FACTOR + 1)
        calls parsePrecedence(PREC_UNARY) to parse right-hand side of '*'


        CALL E: parsePrecedence(PREC_UNARY)
            advance() consumes '3'
            getRule(TOKEN_NUMBER) -> prefix = number
            calls number()

            number()
                emits constant 3

            while PREC_UNARY <= precedence(current token '-')
                compare PREC_UNARY <= PREC_TERM -> false
            CALL E returns to binary()

        binary()
            emits MULTIPLY
        returns to CALL A

    while PREC_ASSIGNMENT <= precedence(current token '-')
        compare PREC_ASSIGNMENT <= PREC_TERM -> true

        advance() consumes '-'
        getRule(TOKEN_MINUS) -> infix = binary
        calls binary()

binary()
    operatorType = TOKEN_MINUS
    getRule(TOKEN_MINUS) -> precedence = PREC_TERM
    calls parsePrecedence(PREC_TERM + 1)
    calls parsePrecedence(PREC_FACTOR) to parser right-hand side of binary

    CALL F: parsePrecedence(PREC_FACTOR)
        advance() consumes '-'
        getRule(TOKEN_MINUS) -> prefix = unary
        calls unary()

        unary()
            operatorType = TOKEN_MINUS
            calls parsePrecedence(PREC_UNARY) to parse operand of unary '-'

            CALL G: parsePrecedence(PREC_UNARY)
                advance() consumes '4'
                getRule(TOKEN_NUMBER) -> prefix = number
                calls number()

            unary()
                emits NEGATE
            returns to CALL F

        while PREC_FACTOR <= precedence(current token EOF)
            compare PREC_FACTOR <= PREC_NONE -> false
        CALL F returns to binary()

    binary()
        emits SUBTRACT
    returns to CALL A

while PREC_ASSIGNMENT <= precedence(current token EOF)
    compare PREC_ASSIGNMENT <= PREC_NONE -> false
CALL A returns


