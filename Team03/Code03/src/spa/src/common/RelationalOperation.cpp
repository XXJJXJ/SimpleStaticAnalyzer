#include "RelationalOperation.h"

RelationalOperation::RelationalOperation(
    string name,
    pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments)
    : Operation(move(name), "relational", arguments) {}

void RelationalOperation::accept(shared_ptr<Visitor> visitor) {
    visitor->visitRelationalOperation(make_shared<RelationalOperation>(*this));
}

bool RelationalOperation::operator==(const Expression& other) const {
    if (!Expression::operator==(other)) {
        return false;
    }

    const RelationalOperation* casted = dynamic_cast<const RelationalOperation*>(&other);
    if (casted == nullptr) {
        return false; 
    }

    return 
        this->getArguments()->first->operator==(*casted->getArguments()->first) &&
        this->getArguments()->second->operator==(*casted->getArguments()->second);
}