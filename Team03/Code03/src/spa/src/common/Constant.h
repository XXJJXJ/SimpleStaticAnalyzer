#pragma once

#include "Expression.h"

class Constant : public Expression {
public:
	explicit Constant(string value);
	void accept(shared_ptr<Visitor> visitor) override;
	bool isLeafNodeExpression() override;
};