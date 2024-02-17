#include "Expression.h"

Expression::Expression(string name_, string expressionType_)
    : name(move(name_)), expressionType(move(expressionType_)) {}

string Expression::getExpressionType() const {
    return expressionType;
}

string Expression::getName() const {
    return name;
}

bool Expression::operator==(const Expression& other) const {
    return expressionType == other.expressionType && name == other.name;
}

optional<Expression::PairOfArguments> Expression::getArguments() const {
    return arguments;
}