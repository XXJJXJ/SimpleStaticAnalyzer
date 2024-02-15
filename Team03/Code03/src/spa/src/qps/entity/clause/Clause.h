#ifndef CLAUSE_H
#define CLAUSE_H

#include "qps/entity/strategy/Strategy.h"

class Clause {
public:
    virtual ~Clause() = default; // Ensure proper deletion of derived classes
    [[nodiscard]] virtual vector<shared_ptr<Strategy>> getStrategies() const = 0; // Pure virtual function
};

#endif // CLAUSE_H
