#include "Operation.h"

Operation::Operation(
    shared_ptr<string> name, 
    shared_ptr<string> type, 
    pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments)
    : Expression(move(name), type) {
        arguments = arguments;
}