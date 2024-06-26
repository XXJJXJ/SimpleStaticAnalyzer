// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
// prompt 2: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
#include "QueryEvaluationContext.h"
#include <algorithm>
#include <string>
#include <sstream>


QueryEvaluationContext::QueryEvaluationContext() {
    queryManager = std::make_shared<QueryManager>();
    predicateResultCache = std::make_shared<PredicateResultCache>();
}

void QueryEvaluationContext::addTableForSynonym(const Synonym& synonym, const std::shared_ptr<HeaderTable> &table) {
    synonymToTableMap[synonym] = table;
}

void QueryEvaluationContext::clearTables() {
    synonymToTableMap.clear();
}

std::shared_ptr<HeaderTable> QueryEvaluationContext::getTableForSynonym(const Synonym& synonym) {
    // If synonym is not in the context, report error
    if (!containsSynonym(synonym)) {
        throw QPSEvaluationException("QEC: Trying to access table for a nonexistent synonym.");
    }
    auto it = synonymToTableMap.find(synonym);
    if (it != synonymToTableMap.end()) {
        return it->second;
    }
    // If table not initialized, it means the synonym is not used in the query, return all entities of the type
    auto entities = queryManager->getAllEntitiesByType(synonym.getType());
    HeaderTable newTable;
    newTable.setHeaders({std::make_shared<Synonym>(synonym)});
    for (const auto& entity : entities) {
        newTable.addRow(TableRow({entity}));
    }
    // Store the table in context
    putTableForSynonymGroup(synonym, std::make_shared<HeaderTable>(newTable));
    return std::make_shared<HeaderTable>(newTable);
}

bool QueryEvaluationContext::containsSynonym(const Synonym& synonym) const {
    // Loop through synonym ptr sets to check if the synonym is present
    for (const auto& group : synonymGroups) {
        if (group.find(std::make_shared<Synonym>(synonym)) != group.end()) {
            return true;
        }
    }
    return false;
}

std::vector<Synonym> QueryEvaluationContext::getSynonyms() const {
    std::vector<Synonym> synonyms;
    for (const auto& pair : synonymToTableMap) {
        synonyms.push_back(pair.first);
    }
    return synonyms;
}

std::shared_ptr<QueryManager> QueryEvaluationContext::getQueryManager() const {
    return queryManager;
}

void QueryEvaluationContext::setQueryManager(const std::shared_ptr<QueryManager>& queryManager) {
    this->queryManager = queryManager;
}

std::vector<std::string> QueryEvaluationContext::getResults() const {
    if (resultTable == nullptr) {
        throw std::runtime_error("No result table present");
    }
    std::unordered_set resultTableString = resultTable->toAttributeStrings(selectedAttributes);
    std::vector<std::string> stringVector(resultTableString.begin(), resultTableString.end());

    return stringVector;

    // return resultTable->toStrings();
}

void QueryEvaluationContext::setResultTable(const shared_ptr<BaseTable> &_resultTable) {
    this->resultTable = _resultTable;
}

/**
 * Checks whether the result is empty. Returns true if any of the tables in the context is empty.
 */
bool QueryEvaluationContext::isCurrentResultEmpty() const {
    if (resultMustBeEmpty) {
        return true;
    }
    for (const auto& pair : synonymToTableMap) {
        if (pair.second->isEmpty()) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<BaseTable> QueryEvaluationContext::getResultTable() const {
    return resultTable;
}

void QueryEvaluationContext::setSynonymGroups(
        const vector<SynonymPtrSet> &synonymGroups) {
    this->synonymGroups = synonymGroups;
}

// ai-gen end

// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/7c590366-8e0e-40e2-863f-2862fa1ae192
bool QueryEvaluationContext::isTableInitialized(const Synonym& synonym) const {
    return synonymToTableMap.find(synonym) != synonymToTableMap.end();
}

void QueryEvaluationContext::putTableForSynonymGroup(const Synonym& synonym, const std::shared_ptr<HeaderTable> &table) {
    // Find the synonym group for the given synonym
    for (const auto& group : synonymGroups) {
        if (group.find(std::make_shared<Synonym>(synonym)) != group.end()) {
            // For each synonym in the group, initialize the table
            for (const auto& syn : group) {
                synonymToTableMap[*syn] = table;
            }
            break;
        }
    }
}

void QueryEvaluationContext::setResultToFalse() {
    resultMustBeEmpty = true;
}

std::vector<SynonymPtrSet> QueryEvaluationContext::getSynonymGroups() const {
    return synonymGroups;
}

std::shared_ptr<PredicateResultCache> QueryEvaluationContext::getCache() const {
    return predicateResultCache;
}

void QueryEvaluationContext::setSelectedAttributes(const vector<shared_ptr<AttributeExtractor>> &selectedAttributes) {
    this->selectedAttributes = selectedAttributes;
}
