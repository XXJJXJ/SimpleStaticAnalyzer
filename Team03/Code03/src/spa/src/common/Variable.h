#pragma once

#include "Expression.h"

class Variable : public Expression {
public:
	Variable(string name);
	void accept(shared_ptr<Visitor> visitor) override;
	inline bool isLeafNodeExpression() override;
};