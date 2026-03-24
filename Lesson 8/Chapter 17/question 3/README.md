## Question 3 Changes

###  Added new token types
In scanner.h, added token kinds for the two new symbols

    TOKEN_QUESTION,
    TOKEN_COLON 

Example:

    typedef enum {
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
    TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
    TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,
    TOKEN_QUESTION, TOKEN_COLON,
    ...
    TOKEN_ERROR,
    TOKEN_EOF
    } TokenType;

### Updated the scanner
In scanner.c, added cases so the scanner returns those tokens:

    case '?': return makeToken(TOKEN_QUESTION);
    case ':': return makeToken(TOKEN_COLON);

### Added a new precedence level
Since ?: should bind more weekly than normal bianry operators like +
and *, I added a new precedence level for conditional expressions.

    typedef enum {
    PREC_NONE,
    PREC_ASSIGNMENT,
    PREC_CONDITIONAL,
    PREC_TERM,
    PREC_FACTOR,
    PREC_UNARY,
    PREC_PRIMARY
    } Precedence;

### Added a ternary parse function
Added a new infix parse function called ternary()
When the parser sees ?, the left-handed condition has already been 
parsed, so this function parses the two remaining operands.

    static void ternary(bool canAssign) {
    (void)canAssign;
    
    parsePrecedence(PREC_ASSIGNMENT);
    consume(TOKEN_COLON, "Expect ':' after then branch of conditional operator.");
    parsePrecedence(PREC_ASSIGNMENT);
    }

### Hooked it into the parse rule table
In complier.c, I added a parse rule for TOKEN_QUESTION:

    [TOKEN_QUESTION] = {NULL, ternary, PREC_CONDITIONAL},
    [TOKEN_COLON]    = {NULL, NULL,    PREC_NONE},

This means:
- ? has no prefix meaning
- ? works an an infix operator
- its infix parse function is ternary 
- it uses conditional precedence