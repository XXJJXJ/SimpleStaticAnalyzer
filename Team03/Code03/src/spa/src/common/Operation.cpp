#include "Operation.h"

Operation::Operation(
    string name, 
    string type, 
    PairOfArguments arguments)
    : Expression(move(name), type) {
        arguments = arguments;
}

string Operation::getName() const {
    return name;
}