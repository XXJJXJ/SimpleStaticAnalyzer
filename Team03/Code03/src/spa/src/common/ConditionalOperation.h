#pragma once

#include "Operation.h"

class ConditionalOperation : public Operation {
public:
	ConditionalOperation(
		string name, 
		pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments);
	void accept(shared_ptr<Visitor> visitor) override;
	bool operator==(const Expression& other) const override;
};