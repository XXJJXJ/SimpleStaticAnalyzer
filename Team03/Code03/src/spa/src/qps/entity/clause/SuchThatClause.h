// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/649c7ba0-9712-44e7-aa24-ca6262c5a922
#ifndef SUCHTHATCLAUSE_H
#define SUCHTHATCLAUSE_H

#include "Clause.h"
#include "Predicate.h"
#include "qps/entity/strategy/Strategy.h"
#include <vector>
#include <memory>

class SuchThatClause : public Clause {
private:
    std::vector<std::shared_ptr<Predicate>> predicates;

public:
    SuchThatClause() = default;
    void addPredicate(std::unique_ptr<Predicate> predicate);
    std::vector<std::shared_ptr<Strategy>> getStrategies() const override;
};

#endif // SUCHTHATCLAUSE_H

// ai-gen end