// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
// prompt 2: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
#pragma once

#ifndef QUERYEVALUATIONCONTEXT_H
#define QUERYEVALUATIONCONTEXT_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "BaseTable.h" // Include the BaseTable class header
#include "qps/entity/query/Synonym.h"
#include "pkb/QueryPKB.h"
#include "qps/entity/evaluation/HeaderTable.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "PredicateResultCache.h"

class QueryEvaluationContext {
private:
    std::unordered_map<Synonym, std::shared_ptr<HeaderTable>> synonymToTableMap;
    bool resultMustBeEmpty = false;    // A quick indicator of empty result, for early termination
    std::shared_ptr<QueryManager> queryManager;
    std::shared_ptr<BaseTable> resultTable;
    std::vector<SynonymPtrSet> synonymGroups;
    std::shared_ptr<PredicateResultCache> predicateResultCache;
    std::vector<shared_ptr<AttributeExtractor>> selectedAttributes;


public:
    QueryEvaluationContext();
    void addTableForSynonym(const Synonym& synonym, const std::shared_ptr<HeaderTable> &table);
    void clearTables();
    [[nodiscard]] std::shared_ptr<HeaderTable> getTableForSynonym(const Synonym& synonym);
    [[nodiscard]] bool containsSynonym(const Synonym& synonym) const;
    [[nodiscard]] bool isTableInitialized(const Synonym& synonym) const;
    void putTableForSynonymGroup(const Synonym& synonym, const std::shared_ptr<HeaderTable> &table);
    [[nodiscard]] std::vector<Synonym> getSynonyms() const;
    [[nodiscard]] std::shared_ptr<QueryManager> getQueryManager() const;
    void setQueryManager(const std::shared_ptr<QueryManager>& queryManager);
    [[nodiscard]] std::vector<std::string> getResults() const;
    void setResultTable(const std::shared_ptr<BaseTable>& _resultTable);
    [[nodiscard]] std::shared_ptr<BaseTable> getResultTable() const;
    [[nodiscard]] bool isCurrentResultEmpty() const;
    void setSynonymGroups(const std::vector<SynonymPtrSet>& synonymGroups);
    [[nodiscard]] std::vector<SynonymPtrSet> getSynonymGroups() const;
    void setResultToFalse();
    [[nodiscard]] std::shared_ptr<PredicateResultCache> getCache() const;
    void setSelectedAttributes(const std::vector<shared_ptr<AttributeExtractor>>& selectedAttributes);
};

#endif // QUERY_EVALUATION_CONTEXT_H


// ai-gen end