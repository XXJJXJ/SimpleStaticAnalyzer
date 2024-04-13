#include "ConditionalOperation.h"

ConditionalOperation::ConditionalOperation(string name, PairOfArguments arguments) : Operation(std::move(name),
                                                                                               EntityType::Conditional,
                                                                                               std::move(arguments)) {}

void ConditionalOperation::accept(shared_ptr<Visitor> visitor) {
    visitor->visitConditionalOperation(make_shared<ConditionalOperation>(*this));
}

bool ConditionalOperation::operator==(const Expression &other) const {
    if (!(Expression::operator==(other))) {
        return false;
    } else {
        auto &casted = static_cast<const ConditionalOperation &>(other);
        auto &thisFirstArgument = this->getArguments()->first;
        auto &thisSecondArgument = this->getArguments()->second;
        auto &castedFirstArgument = casted.getArguments()->first;
        auto &castedSecondArgument = casted.getArguments()->second;
        if (!(thisFirstArgument->operator==(*castedFirstArgument))) {
            return false;
        } else {
            if (thisSecondArgument == NULL && castedSecondArgument == NULL) {
                return true;
            } else {
                return thisSecondArgument->operator==(*castedSecondArgument);
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
