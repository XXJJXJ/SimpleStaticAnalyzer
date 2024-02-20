// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
// prompt 2: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
#include "QueryEvaluationContext.h"
#include <algorithm>
#include <string>
#include <sstream>


QueryEvaluationContext::QueryEvaluationContext() : queryManager(std::make_shared<QueryManager>()) {}

void QueryEvaluationContext::addTableForSynonym(const Synonym& synonym, const std::shared_ptr<Table>& table) {
    synonymToTableMap[synonym] = table;
}

void QueryEvaluationContext::clearTables() {
    synonymToTableMap.clear();
}

std::shared_ptr<Table> QueryEvaluationContext::getTableForSynonym(const Synonym& synonym) const {
    auto it = synonymToTableMap.find(synonym);
    if (it != synonymToTableMap.end()) {
        return it->second;
    }
    return nullptr;
}

bool QueryEvaluationContext::containsSynonym(const Synonym& synonym) const {
    return synonymToTableMap.find(synonym) != synonymToTableMap.end();
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
    return resultTable->toStrings();
}

void QueryEvaluationContext::setResultTable(const shared_ptr<Table> &_resultTable) {
    this->resultTable = _resultTable;
}

/**
 * Checks whether the result is empty. Returns true if any of the tables in the context is empty.
 */
bool QueryEvaluationContext::isResultEmpty() const {
    for (const auto& pair : synonymToTableMap) {
        auto &table = pair.second;
        if (table->isEmpty()) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Table> QueryEvaluationContext::getResultTable() const {
    return resultTable;
}






