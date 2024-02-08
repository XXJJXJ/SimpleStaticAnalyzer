#pragma once

#include "Expression.h"

class Operation : public Expression {
public:
    Operation(string name,
        string type,
        pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments);
};