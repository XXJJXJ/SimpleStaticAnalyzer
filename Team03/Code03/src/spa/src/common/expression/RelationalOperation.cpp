#include "RelationalOperation.h"

RelationalOperation::RelationalOperation(string name, PairOfArguments arguments) : Operation(std::move(name),
                                                                                             EntityType::Relational,
                                                                                             std::move(arguments)) {}

void RelationalOperation::accept(shared_ptr<Visitor> visitor) {
    visitor->visitRelationalOperation(make_shared<RelationalOperation>(*this));
}

bool RelationalOperation::operator==(const Expression &other) const {
    if (!Expression::operator==(other)) {
        return false;
    } else {
        auto &casted = static_cast<const RelationalOperation &>(other);
        auto &thisFirstArgument = this->getArguments()->first;
        auto &thisSecondArgument = this->getArguments()->second;
        auto &castedFirstArgument = *casted.getArguments()->first;
        auto &castedSecondArgument = *casted.getArguments()->second;
        return thisFirstArgument->operator==(castedFirstArgument)
            && thisSecondArgument->operator==(castedSecondArgument);
    }
}

EntityType RelationalOperation::getType() const {
    return EntityType::Relational;
}

bool RelationalOperation::isOfType(EntityType type) const {
    return type == EntityType::Relational || Operation::isOfType(type);
}