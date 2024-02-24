// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
// prompt 2: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
#pragma once

#ifndef QUERYEVALUATIONCONTEXT_H
#define QUERYEVALUATIONCONTEXT_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "HeaderTable.h" // Include the HeaderTable class header
#include "qps/entity/query/Synonym.h"
#include "pkb/QueryPKB.h"

class QueryEvaluationContext {
private:
    std::unordered_map<Synonym, std::shared_ptr<HeaderTable>> synonymToTableMap;
    std::shared_ptr<QueryManager> queryManager;
    std::shared_ptr<HeaderTable> resultTable;
    std::vector<std::unordered_set<std::shared_ptr<Synonym>>> synonymGroups;

public:
    QueryEvaluationContext();
    void addTableForSynonym(const Synonym& synonym, const std::shared_ptr<HeaderTable>& table);
    void clearTables();
    [[nodiscard]] std::shared_ptr<HeaderTable> getTableForSynonym(const Synonym& synonym) const;
    [[nodiscard]] bool containsSynonym(const Synonym& synonym) const;
    [[nodiscard]] bool isTableInitialized(const Synonym& synonym) const;
    void putTableForSynonymGroup(const Synonym& synonym, const std::shared_ptr<HeaderTable>& table);
    [[nodiscard]] std::vector<Synonym> getSynonyms() const;
    [[nodiscard]] std::shared_ptr<QueryManager> getQueryManager() const;
    void setQueryManager(const std::shared_ptr<QueryManager>& queryManager);
    [[nodiscard]] std::vector<std::string> getResults() const;
    void setResultTable(const std::shared_ptr<HeaderTable>& _resultTable);
    [[nodiscard]] std::shared_ptr<HeaderTable> getResultTable() const;
    [[nodiscard]] bool isResultEmpty() const;
    void setSynonymGroups(const std::vector<std::unordered_set<std::shared_ptr<Synonym>>>& synonymGroups);
};

#endif // QUERY_EVALUATION_CONTEXT_H


// ai-gen end