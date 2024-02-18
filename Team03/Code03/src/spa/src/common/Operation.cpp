#include "Operation.h"

Operation::Operation(
    string name, 
    string type, 
    PairOfArguments arguments_)
    : Expression(move(name), type) {
        arguments = arguments_;
}

string Operation::getName() const {
    return name;
}