#include "ArithmeticOperation.h"

ArithmeticOperation::ArithmeticOperation(
    string name,
    PairOfArguments arguments)
    : Operation(move(name), "arithmetic", arguments) {}

void ArithmeticOperation::accept(shared_ptr<Visitor> visitor) {
    visitor->visitArithmeticalOperation(make_shared<ArithmeticOperation>(*this));
}

bool ArithmeticOperation::operator==(const Expression& other) const {
    if (!Expression::operator==(other)) {
        return false;
    }

    const ArithmeticOperation* casted = dynamic_cast<const ArithmeticOperation*>(&other);
    if (casted == nullptr) {
        return false; 
    }

    return 
        this->getArguments()->first->operator==(*casted->getArguments()->first) &&
        this->getArguments()->second->operator==(*casted->getArguments()->second);
}

