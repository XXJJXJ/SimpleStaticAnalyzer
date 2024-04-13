#include "Constant.h"

Constant::Constant(string value) 
    : Expression(std::move(value),
        EntityType::Constant) {}

void Constant::accept(shared_ptr<Visitor> visitor) {
    visitor->visitConstant(make_shared<Constant>(*this));
}

bool Constant::isLeafNode() {
    return true;
}

std::size_t Constant::hash() const {
    std::hash<string> hasher;
    return hasher(getName());
}

bool Constant::operator==(const Constant& other) const {
    return getName() == other.getName();
}

EntityType Constant::getType() const {
    return EntityType::Constant;
}

bool Constant::isOfType(EntityType type) const {
    return type == EntityType::Constant || Expression::isOfType(type);
}

int Constant::getValue() const {
    return stoi(getName());
}
