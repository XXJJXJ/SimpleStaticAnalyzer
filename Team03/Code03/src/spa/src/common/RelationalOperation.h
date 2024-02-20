#pragma once

#include "Operation.h"
#include "Util.h"

using namespace std;

class RelationalOperation : public Operation {
public:
	RelationalOperation(
		string name, 
		PairOfArguments arguments);
	void accept(shared_ptr<Visitor> visitor) override;
	bool operator==(const Expression& other) const override;
};