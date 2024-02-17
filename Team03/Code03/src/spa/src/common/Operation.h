#pragma once

#include "Expression.h"
#include "Util.h"

class Operation : public Expression {
public:
    Operation(
        string name,
        string type,
        PairOfArguments arguments);
    string getName() const override;
};