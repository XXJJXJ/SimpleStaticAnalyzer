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

    const ConditionalOperation* casted = dynamic_cast<const ConditionalOperation*>(&other);
    if (casted == nullptr) {
        return false; 
    }

    return 
        this->getArguments()->first->operator==(*casted->getArguments()->first) &&
        this->getArguments()->second->operator==(*casted->getArguments()->second);
}