#include "CallStatement.h"

CallStatement::CallStatement(int statementNumber,
    shared_ptr<Procedure> procedure_,
    string procedureName) :
    procedure(std::move(procedure_)),
    Statement(
        statementNumber,
        EntityType::Call,
        procedureName) {}

void CallStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitCallStatement(make_shared<CallStatement>(*this));
}

string CallStatement::getTargetProcedureName() const {
    return procedure->getName();
}

EntityType CallStatement::getType() const {
    return EntityType::Call;
}

bool CallStatement::isOfType(EntityType type) const {
    return type == EntityType::Call || Statement::isOfType(type);
}