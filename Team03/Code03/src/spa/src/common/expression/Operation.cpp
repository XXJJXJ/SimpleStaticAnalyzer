#include "Operation.h"

Operation::Operation(
    string name, 
    EntityType operationType, 
    PairOfArguments arguments_)
    : Expression(std::move(name), std::move(operationType)) {
        arguments = std::move(arguments_);
}

string Operation::getName() const {
    return name;
}

EntityType Operation::getType() const {
    return EntityType::Operation;
}

bool Operation::isOfType(EntityType type) const {
    return type == EntityType::Operation || Expression::isOfType(type);
}
