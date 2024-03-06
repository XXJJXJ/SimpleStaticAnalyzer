#include "CallStatement.h"

CallStatement::CallStatement(int statementNumber,
    Procedure procedure_,
    string procedureName) :
    procedure(move(procedure_)),
    Statement(
        statementNumber,
        EntityType::Call,
        procedureName) {}

void CallStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitCallStatement(make_shared<CallStatement>(*this));
}

string CallStatement::getProcedureName() {
    return procedure.getName();
}

EntityType CallStatement::getType() const {
    return EntityType::Call;
}

bool CallStatement::isOfType(EntityType type) const {
    return type == EntityType::Call || Statement::isOfType(type);
}
