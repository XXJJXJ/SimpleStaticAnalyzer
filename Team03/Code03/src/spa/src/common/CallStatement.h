#pragma once

#include "Statement.h"
#include "Procedure.h"

class CallStatement : public Statement {
public:
    CallStatement(
        int statementNumber,
        Procedure procedure,
        string procedureName);
    void accept(shared_ptr<Visitor> visitor) override;
    string getProcedureName();
    [[nodiscard]] EntityType getType() const override;
    [[nodiscard]] bool isOfType(EntityType type) const override;

private:
    Procedure procedure;
};

