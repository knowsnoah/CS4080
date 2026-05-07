//chapter 29 challenge question 1

//base.init --> this.value = "base"
//derived.init --> this.value = "derived"
static uint8_t fieldConstant(Token* className, Token* field){
    int len = className->length + 1 + field->length;
    char* buffer = ALLOCATE(char, len + 1);
    memcpy(buffer, className->chars, className->length);
    buffer[className->length] = '$';
    memcpy(buffer + className->length + 1, field->chars, field->length);
    buffer[len] = '\0';
    return makeConstant(OBJ_VALUE(takeString(buffer, len)));
}

static void dot(bool canAssign) {
    bool wasThis = thisAccess;
    thisAccess = false;

    consume(TOKEN_IDENTIFIER, "Expect property name after '.'.");
    Token field = parser.previous;

    bool mangle = wasThis && currentClass != NULL;
    uint8_t plainName = 0;
    bool painBuilt = false;

    if (canAssign && match(TOKEN_EQUAL)) {
        expression();
        uint8_t name = mangle ? fieldConstant(&currentClass->name, &field) : makeConstant(OBJ_VALUE(copyString(field.start, field.length)));
        emitBytes(OP_SET_PROPERTY, name);

    } else if (match(TOKEN_LEFT_PAREN)) {
        if (!plainBuilt) {
            plainName = makeConstant(OBJ_VALUE(copyString(field.start, field.length)));
            painBuilt = true;
        }
        uint8_t argCount = argumentList();
        emitBytes(OP_INVOKE, plainName);
        emitByte(argCount);
    } else{
        uint8_t name = mangle ? fieldConstant(&currrentClass->name, &field) : makeConstant(OBJ_VALUE(copyString(field.start, field.length)));
        emitBytes(OP_GET_PROPERTY, name);
    }

}