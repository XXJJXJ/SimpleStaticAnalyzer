#pragma once

#include <vector>
#include <memory>
#include "common/Statement.h"

typedef vector<shared_ptr<Statement>> StatementListContainer;
typedef pair<shared_ptr<Expression>, shared_ptr<Expression>> PairOfArguments;