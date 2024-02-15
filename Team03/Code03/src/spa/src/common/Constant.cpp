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