#include "Expression.h"

Expression::Expression(string name, string expression_type)
    : name(move(name)), expression_type(move(expression_type)) {}

string Expression::getExpressionType() const {
    return expression_type;
}

string Expression::getName() const {
    return name;
}

bool Expression::operator==(const Expression& other) const {
    return expression_type == other.expression_type && name == other.name;
}

optional<Expression::PairOfArguments> Expression::getArguments() const {
    return arguments;
}