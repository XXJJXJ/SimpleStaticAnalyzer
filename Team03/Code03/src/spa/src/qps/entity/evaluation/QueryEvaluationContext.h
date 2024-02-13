// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
#pragma once

#include "SynonymValues.h"
#include "pkb/QueryPKB.h"
#include <list>

class QueryEvaluationContext {
private:
    std::list<SynonymValues> synonymValuesList;
    shared_ptr<QueryManager> queryManager;

public:
    QueryEvaluationContext();
    void addSynonymValues(const SynonymValues& synonymValues);
    void clearSynonymValuesList();
    [[nodiscard]] SynonymValues getSynonymValues(const Synonym& synonym) const;
    [[nodiscard]] bool containsSynonym(const Synonym& synonym) const;
    [[nodiscard]] std::list<Synonym> getSynonyms() const;
    [[nodiscard]] shared_ptr<QueryManager> getQueryManager() const;
    [[nodiscard]] vector<string>getResults() const;
    void setQueryManager(const shared_ptr<QueryManager>& queryManager1);
};
// ai-gen end