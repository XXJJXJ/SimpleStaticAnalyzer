#include "Operation.h"

Operation::Operation(
    string name, 
    string type, 
    pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments_)
    : Expression(move(name), type) {
        arguments = arguments_;
}

string Operation::getName() const {
    return name;
}