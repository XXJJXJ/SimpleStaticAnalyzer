#pragma once

#include "Operation.h"
#include "common/Util.h"

class ConditionalOperation : public Operation {
public:
    ConditionalOperation(string name, PairOfArguments arguments);
    void accept(shared_ptr<Visitor> visitor) override;
    bool operator==(const Expression &other) const override;
    [[nodiscard]] EntityType getType() const override;
    [[nodiscard]] bool isOfType(EntityType type) const override;
};