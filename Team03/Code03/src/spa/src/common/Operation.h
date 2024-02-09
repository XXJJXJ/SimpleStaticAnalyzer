#pragma once

#include "Expression.h"

class Operation : public Expression {
public:
    Operation(
        shared_ptr<string> name,
        shared_ptr<string> type,
        pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments);
};