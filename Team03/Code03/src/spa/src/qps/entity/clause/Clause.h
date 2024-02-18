
// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/649c7ba0-9712-44e7-aa24-ca6262c5a922
#ifndef CLAUSE_H
#define CLAUSE_H

#include "qps/entity/strategy/Strategy.h"

class Clause {
public:
    virtual ~Clause() = default; // Ensure proper deletion of derived classes
    [[nodiscard]] virtual vector<shared_ptr<Strategy>> getStrategies() const = 0; // Pure virtual function
};

#endif // CLAUSE_H

// ai-gen end