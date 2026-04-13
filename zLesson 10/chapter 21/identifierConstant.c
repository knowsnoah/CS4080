//Chapter 21: Challenge Question 1

//adjusting this method
static uint_t identifierConstant(Token* name) {
    //check if this vairable name is already in the constants table
    for (int i=0; i < cureentChunk()->constant.count; i++) {
        Value existing = currentChunk()->constants.values[i];
        if (!IS_STRING(existing)) continue; //skip non-string constants
        ObjString *exsistingStr = AS_STRING(existing);

        //check if the lengths and characters match
        if (existingStr->length == name->length &&
            memcmp(existingStr->chars, name->start, name->length) == 0) {
            reutnr (uint_t)i; //reuse the exsiting slot
        }
    }

    return makeConstant(OBJ_VAL(copyString(name->start, name->length))); //use new slot
}
