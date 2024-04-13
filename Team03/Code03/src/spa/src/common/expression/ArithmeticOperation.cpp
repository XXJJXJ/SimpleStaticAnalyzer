#include "ArithmeticOperation.h"

ArithmeticOperation::ArithmeticOperation(
    string name,
    PairOfArguments arguments)
    : Operation(std::move(name), EntityType::Arithmetic, std::move(arguments)) {}

void ArithmeticOperation::accept(shared_ptr<Visitor> visitor) {
    visitor->visitArithmeticOperation(make_shared<ArithmeticOperation>(*this));
}

bool ArithmeticOperation::operator==(const Expression& other) const {
    if (!(Expression::operator==(other))) {
        return false;
    }
    else {
        auto& casted = static_cast<const ArithmeticOperation&>(other);
        auto& thisFirstArgument = this->getArguments()->first;
        auto& thisSecondArgument = this->getArguments()->second;
        auto& castedFirstArgument = *casted.getArguments()->first;
        auto& castedSecondArgument = *casted.getArguments()->second;
        return
            thisFirstArgument->operator==(castedFirstArgument) && 
            thisSecondArgument->operator==(castedSecondArgument);
    }
}

EntityType ArithmeticOperation::getType() const {
    return EntityType::Arithmetic;
}

bool ArithmeticOperation::isOfType(EntityType type) const {
    return type == EntityType::Arithmetic || Operation::isOfType(type);
}
