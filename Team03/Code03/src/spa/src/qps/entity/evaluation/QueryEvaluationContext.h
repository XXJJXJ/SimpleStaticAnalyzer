// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
#pragma once

#include "SynonymValues.h"
#include "qps/entity/strategy/Strategy.h"
#include "pkb/QueryPKB.h"
#include <list>

class QueryEvaluationContext {
private:
    std::list<SynonymValues> synonymValuesList;
    shared_ptr<QueryManager> queryManager;

public:
    QueryEvaluationContext();
    void addSynonymValues(const SynonymValues& synonymValues);
    [[nodiscard]] shared_ptr<QueryManager> getQueryManager() const;
    [[nodiscard]] SynonymValues getSynonymValues(const Synonym& synonym) const;

};
// ai-gen end