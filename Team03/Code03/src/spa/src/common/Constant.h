#pragma once

#include "Expression.h"

class Constant : public Expression {
public:
	explicit Constant(string name);
	void accept(shared_ptr<Visitor> visitor) override;
	bool isLeafNodeExpression() override;
};