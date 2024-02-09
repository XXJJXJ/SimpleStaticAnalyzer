#include "Expression.h"

Expression::Expression(string name, string expressionType)
    : name(move(name)), expressionType(move(expressionType)) {}

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