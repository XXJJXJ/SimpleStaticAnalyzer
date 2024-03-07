#pragma once

#include "Statement.h"

class CallStatement : public Statement {
public:
    [[nodiscard]] EntityType getType() const override;
    [[nodiscard]] bool isOfType(EntityType type) const override;
    string getTargetProcedureName();
};

