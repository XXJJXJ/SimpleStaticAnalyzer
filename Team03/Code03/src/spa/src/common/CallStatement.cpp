#include "CallStatement.h"

EntityType CallStatement::getType() const {
    return EntityType::Call;
}

bool CallStatement::isOfType(EntityType type) const {
    return type == EntityType::Call || Statement::isOfType(type);
}

string CallStatement::getTargetProcedureName() {
    // TODO: Get target procedure name in call statement
    return "";
}