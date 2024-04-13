#pragma once

#include "Operation.h"
#include "common/Util.h"

using namespace std;

class ArithmeticOperation : public Operation {
public:
    ArithmeticOperation(string name, PairOfArguments arguments);
    void accept(shared_ptr<Visitor> visitor) override;
    bool operator==(const Expression &other) const override;
    [[nodiscard]] EntityType getType() const override;
    [[nodiscard]] bool isOfType(EntityType type) const override;

};