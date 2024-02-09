#include "Variable.h"

Variable::Variable(shared_ptr<string> name) : Expression(move(name),
    make_shared<string>("variable")) {}

void Variable::accept(shared_ptr<Visitor> visitor) {
    visitor->visitVariable(make_shared<Variable>(*this));
}

bool Variable::isLeafNodeExpression() {
    return true;
}