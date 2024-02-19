#pragma once

#include "Operation.h"
#include "Util.h"

using namespace std;

class ArithmeticOperation : public Operation {
public:
	ArithmeticOperation(
		string name, 
		PairOfArguments arguments);
	void accept(shared_ptr<Visitor> visitor) override;
	bool operator==(const Expression& other) const override;
};