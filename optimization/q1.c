//Chapter 30 Challenge Question 1

//Fire up your profiler, run a 
//couple of benchmarks, and look for other hotspots in 
//the VM. Do you see anything in the runtime 
//that you can improve

//optimizing code
fun run(limit) {
    var i = 0;
    var total = 0;
    var guard = 1;

    while (i<limit) {
        total = total + i * 3 - i / 2 + guard;
        
        if (total > 1000000) {
            total = total - 1000000;
            guard = guard + 1;
        } else {
            guard = guard + 2;
        }

        if (guard > 50 and total < 500000) {
            guard = 1;
        }

        i = i + 1;
    }

    return total + guard;
}

var start = clock();
var answer = run(35000000);
print clock() - start;
print answer;


//one less push and pop
#define BINARY_OP(valueType, op)
do {
    if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) {
        runtimeError("Operands must be numbers.");
        return INTERPRET_RUNTIME_ERROR;
    }

    double b = AS_NUMBER(pop());
    vm.stackTop[-1] = valueType(AS_NUMBER(vm.stackTop[-1]) op b);
} while (false)

