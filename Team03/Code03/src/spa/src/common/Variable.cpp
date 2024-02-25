#include "Variable.h"

Variable::Variable(string name) : Expression(std::move(name), EntityType::Variable) {}

void Variable::accept(shared_ptr<Visitor> visitor) {
    visitor->visitVariable(make_shared<Variable>(*this));
}

bool Variable::isLeafNodeExpression() {
    return true;
}

string Variable::getName() const {
    return name;
}

std::size_t Variable::hash() const {
    std::hash<string> hasher;
    return hasher(getName());
}

bool Variable::operator==(const Variable& other) const {
    return (getName() == other.getName());
}

EntityType Variable::getType() const {
    return EntityType::Variable;
}

bool Variable::isOfType(EntityType type) const {
    return type == EntityType::Variable || Expression::isOfType(type);
}
