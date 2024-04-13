#pragma once

#include "Expression.h"
#include "common/Util.h"

class Operation : public Expression {
public:
    Operation(
        string name,
        EntityType operationType,
        PairOfArguments arguments);
    string getName() const override;
    [[nodiscard]] EntityType getType() const override;
    [[nodiscard]] bool isOfType(EntityType type) const override;
};