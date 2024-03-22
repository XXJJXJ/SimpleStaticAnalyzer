#include "ConditionalOperation.h"

ConditionalOperation::ConditionalOperation(
    string name,
    PairOfArguments arguments)
    : Operation(std::move(name), EntityType::Conditional, std::move(arguments)) {}

void ConditionalOperation::accept(shared_ptr<Visitor> visitor) {
    visitor->visitConditionalOperation(make_shared<ConditionalOperation>(*this));
}

bool ConditionalOperation::operator==(const Expression& other) const {
    if (!(Expression::operator==(other))) {
        return false;
    }
    else {
        auto& casted = static_cast<const ConditionalOperation&>(other);
        auto& thisPairOfArguments = this->getArguments();
        auto& castedPairOfArguments = casted.getArguments();
        if (!(thisPairOfArguments->first->operator==(*castedPairOfArguments->first))) {
            return false;
        }
        else {
            if (thisPairOfArguments->second == NULL && 
                castedPairOfArguments->second == NULL) {
                return true;
            }
            else {
                return thisPairOfArguments->second->operator==(*castedPairOfArguments->second);
            }
        }
    }
}

EntityType ConditionalOperation::getType() const {
    return EntityType::Conditional;
}

bool ConditionalOperation::isOfType(EntityType type) const {
    return type == EntityType::Conditional || Operation::isOfType(type);
}
