// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
// prompt 2: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
#pragma once

#ifndef QUERYEVALUATIONCONTEXT_H
#define QUERYEVALUATIONCONTEXT_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "Table.h" // Include the Table class header
#include "qps/entity/query/Synonym.h"
#include "pkb/QueryPKB.h"

class QueryEvaluationContext {
private:
    std::unordered_map<Synonym, std::shared_ptr<Table>> synonymToTableMap;
    std::shared_ptr<QueryManager> queryManager;
    std::shared_ptr<Table> resultTable;

public:
    QueryEvaluationContext();
    void addTableForSynonym(const Synonym& synonym, const std::shared_ptr<Table>& table);
    void clearTables();
    [[nodiscard]] std::shared_ptr<Table> getTableForSynonym(const Synonym& synonym) const;
    [[nodiscard]] bool containsSynonym(const Synonym& synonym) const;
    [[nodiscard]] std::vector<Synonym> getSynonyms() const;
    [[nodiscard]] std::shared_ptr<QueryManager> getQueryManager() const;
    void setQueryManager(const std::shared_ptr<QueryManager>& queryManager);
    [[nodiscard]] std::vector<std::string> getResults() const;
    void setResultTable(const std::shared_ptr<Table>& _resultTable);
    bool isResultEmpty() const;
};

#endif // QUERYEVALUATIONCONTEXT_H

// ai-gen end