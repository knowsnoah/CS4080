//Challenge Question 2

//Change 1: added beginScope() and endScope() functions calls to give
//each iteration a new variable scope.
// This lets eeach closure capture its own separate value

beginScope(); //fresh scope for each loop iteration
statement();  //closure capture this fresh variable 
endScope();

emitLoop(loopStart);