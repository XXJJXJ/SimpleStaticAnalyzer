#include "ConditionalOperation.h"

ConditionalOperation::ConditionalOperation(
    string name,
    pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments)
    : Operation(move(name), "conditional", arguments) {}

void ConditionalOperation::accept(shared_ptr<Visitor> visitor) {
    visitor->visitConditionalOperation(make_shared<ConditionalOperation>(*this));
}

bool ConditionalOperation::operator==(const Expression& other) const {
    if (!Expression::operator==(other)) {
        return false;
    }
   
    auto casted = dynamic_cast<const ConditionalOperation&>(other);
    if (!this->getArguments()->first->operator==(*casted.getArguments()->first)) {
        return false;
    }

    if (this->getArguments()->second == NULL
        && casted.getArguments()->second == NULL) {
        return true;
    }

    return this->getArguments()->second->operator==(*casted.getArguments()->second);
}