#include "Constant.h"

Constant::Constant(string name) 
    : Expression(move(name),
        "constant") {}

void Constant::accept(shared_ptr<Visitor> visitor) {
    visitor->visitConstant(make_shared<Constant>(*this));
}

bool Constant::isLeafNodeExpression() {
    return true;
}

std::size_t Constant::hash() const {
    std::hash<string> hasher;
    return hasher(getName());
}

bool Constant::operator==(const Constant& other) const {
    return getName() == other.getName();
}