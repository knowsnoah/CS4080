//Chapter 30 Challenge Question 2

//add a new type of object to the VM, such as a short string that is optimized for small strings.
typedef enum {
    //..
    OBJ_SHORT_STRING,
    //..
} ObjType;

struct ObjShortString {
    Obj obj;
    uint32_t hash;
    char chars[8]; //8 chars = 64 bits
};

//and everywhere else strings are used...
Value takeStringValue(char* chars, int length) {
    if (length <= SHORT_STRING_MAX) {
        Value value = SHORT_STRING_VAL(chars, length);
        FREE_ARRAY(char, chars, length + 1);
        return value;
    }

    return OBJ_VAL(takeString(chars, length));
 }

 fun run(limit) {
    var i = 0;
    var total = 0;
    var left = "a";
    var right = "b";

    while (i<limit) {
        var pair = left + right;

        if (pair == "ab") {
            total = total + 1;
            left = "g";
            right = "d";
        } else if (pair == "gd") {
            total = total + 2;
            left = "a";
            right = "d";
        
        } else if (pair == "ad") {
            total = total + 3;
            left = "g";
            right = "b";
        } else if (pair == "gb") {
            total = total + 4;
            left = "a";
            right = "b";
        }

        i = i + 1;
    }

    return total;
 }

 var start = clock();
 var answer = run(10000000);
 print clock() - start;
 print answer;