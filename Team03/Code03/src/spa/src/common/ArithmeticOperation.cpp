#include "ArithmeticOperation.h"

ArithmeticOperation::ArithmeticOperation(
    string name,
    PairOfArguments arguments)
    : Operation(std::move(name), EntityType::Arithmetic, std::move(arguments)) {}

void ArithmeticOperation::accept(shared_ptr<Visitor> visitor) {
    visitor->visitArithmeticalOperation(make_shared<ArithmeticOperation>(*this));
}

bool ArithmeticOperation::operator==(const Expression& other) const {
    if (!(Expression::operator==(other))) {
        return false;
    }
    else {
        auto casted = dynamic_cast<const ArithmeticOperation&>(other);
        auto& thisPairOfArguments = this->getArguments();
        auto& castedPairOfArguments = casted.getArguments();
        return
            thisPairOfArguments->first->operator==(*castedPairOfArguments->first) && 
            thisPairOfArguments->second->operator==(*castedPairOfArguments->second);
    }
}

EntityType ArithmeticOperation::getType() const {
    return EntityType::Arithmetic;
}

bool ArithmeticOperation::isOfType(EntityType type) const {
    return type == EntityType::Arithmetic || Operation::isOfType(type);
}
