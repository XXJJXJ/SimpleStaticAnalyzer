#pragma once

#include "Statement.h"
#include "common/Procedure.h"

class CallStatement : public Statement {
public:
    CallStatement(
        int statementNumber,
        shared_ptr<Procedure> procedure,
        string procedureName);
    void accept(shared_ptr<Visitor> visitor) override;
    string getTargetProcedureName() const;
    [[nodiscard]] EntityType getType() const override;
    [[nodiscard]] bool isOfType(EntityType type) const override;

private:
    shared_ptr<Procedure> procedure;
};