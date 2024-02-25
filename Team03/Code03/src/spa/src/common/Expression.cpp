#include "Expression.h"

Expression::Expression(string name_, EntityType expressionType_)
    : name(std::move(name_)), expressionType(std::move(expressionType_)) {}

EntityType Expression::getExpressionType() const {
    return expressionType;
}

string Expression::getName() const {
    return name;
}

bool Expression::operator==(const Expression& other) const {
    return expressionType == other.expressionType && name == other.name;
}

optional<PairOfArguments> Expression::getArguments() const {
    return arguments;
}

EntityType Expression::getType() const {
    return EntityType::Expression;
}

bool Expression::isOfType(EntityType type) const {
    return type == EntityType::Expression;
}

