#include "Expression.h"

Expression::Expression(shared_ptr<string> name, shared_ptr<string> expressionType)
    : name(move(name)), expressionType(move(expressionType)) {}

shared_ptr<string> Expression::getExpressionType() const {
    return expressionType;
}

shared_ptr<string> Expression::getName() const {
    return name;
}

bool Expression::operator==(const Expression& other) const {
    return expressionType == other.expressionType && name == other.name;
}

optional<Expression::PairOfArguments> Expression::getArguments() const {
    return arguments;
}