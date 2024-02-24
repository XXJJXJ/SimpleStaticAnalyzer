#include "ArithmeticOperation.h"

ArithmeticOperation::ArithmeticOperation(
    string name,
    PairOfArguments arguments)
    : Operation(move(name), EntityType::Arithmetic, arguments) {}

void ArithmeticOperation::accept(shared_ptr<Visitor> visitor) {
    visitor->visitArithmeticalOperation(make_shared<ArithmeticOperation>(*this));
}

bool ArithmeticOperation::operator==(const Expression& other) const {
    if (!Expression::operator==(other)) {
        return false;
    }

    auto casted = dynamic_cast<const ArithmeticOperation&>(other);

    return
        this->getArguments()->first->operator==(*casted.getArguments()->first) && 
        this->getArguments()->second->operator==(*casted.getArguments()->second);
}

EntityType ArithmeticOperation::getType() const {
    return EntityType::Arithmetic;
}

bool ArithmeticOperation::isOfType(EntityType type) const {
    return type == this->getType() || Operation::isOfType(type);
}
