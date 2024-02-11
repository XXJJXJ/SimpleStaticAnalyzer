#include "Variable.h"

Variable::Variable(string name) : Expression(move(name),"variable") {}

void Variable::accept(shared_ptr<Visitor> visitor) {
    visitor->visitVariable(make_shared<Variable>(*this));
}

bool Variable::isLeafNodeExpression() {
    return true;
}