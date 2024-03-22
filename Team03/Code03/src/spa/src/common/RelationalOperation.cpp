#include "RelationalOperation.h"

RelationalOperation::RelationalOperation(
    string name,
    PairOfArguments arguments)
    : Operation(std::move(name), EntityType::Relational, std::move(arguments)) {}

void RelationalOperation::accept(shared_ptr<Visitor> visitor) {
    visitor->visitRelationalOperation(make_shared<RelationalOperation>(*this));
}

bool RelationalOperation::operator==(const Expression& other) const {
    if (!Expression::operator==(other)) {
        return false;
    }
    else {
        auto& casted = dynamic_cast<const RelationalOperation&>(other);
        auto& thisPairOfArguments = this->getArguments();
        auto& castedPairOfArguments = casted.getArguments();
        return
            thisPairOfArguments->first->operator==(*castedPairOfArguments->first) && 
            thisPairOfArguments->second->operator==(*castedPairOfArguments->second);
    }
}

EntityType RelationalOperation::getType() const {
    return EntityType::Relational;
}

bool RelationalOperation::isOfType(EntityType type) const {
    return type == EntityType::Relational || Operation::isOfType(type);
}