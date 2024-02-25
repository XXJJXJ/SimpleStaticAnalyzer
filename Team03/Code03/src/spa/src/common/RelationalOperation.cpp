#include "RelationalOperation.h"

RelationalOperation::RelationalOperation(
    string name,
    PairOfArguments arguments)
    : Operation(std::move(name), EntityType::Relational, arguments) {}

void RelationalOperation::accept(shared_ptr<Visitor> visitor) {
    visitor->visitRelationalOperation(make_shared<RelationalOperation>(*this));
}

bool RelationalOperation::operator==(const Expression& other) const {
    if (!Expression::operator==(other)) {
        return false;
    }

    auto casted = dynamic_cast<const RelationalOperation&>(other);
    return
        this->getArguments()->first->operator==(*casted.getArguments()->first) && 
        this->getArguments()->second->operator==(*casted.getArguments()->second);
}

EntityType RelationalOperation::getType() const {
    return EntityType::Relational;
}

bool RelationalOperation::isOfType(EntityType type) const {
    return type == EntityType::Relational || Operation::isOfType(type);
}