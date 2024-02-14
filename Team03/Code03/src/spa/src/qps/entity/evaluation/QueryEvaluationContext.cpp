// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
#include "QueryEvaluationContext.h"
#include <algorithm>
#include <string>
#include <sstream>

void QueryEvaluationContext::addSynonymValues(const SynonymValues& synonymValues) {
    synonymValuesList.push_back(synonymValues);
}

// ai-gen end
QueryEvaluationContext::QueryEvaluationContext() {
    synonymValuesList = std::list<SynonymValues>();
    queryManager = std::make_shared<QueryManager>();
}

shared_ptr<QueryManager> QueryEvaluationContext::getQueryManager() const {
    return queryManager;
}

vector<string> QueryEvaluationContext::getResults() const {
    // ensures that there's only one synonym list left
    // prompt: https://chat.openai.com/share/b8694b03-2e9e-465e-a3fb-e31d4fbe079a
    if (synonymValuesList.size() != 1) {
        throw std::runtime_error("There should be exactly one synonym list left");
    }
    return synonymValuesList.front().toStringList();
}

void QueryEvaluationContext::setQueryManager(const shared_ptr<QueryManager>& queryManager1) {
    this->queryManager = queryManager1;
}

SynonymValues QueryEvaluationContext::getSynonymValues(const Synonym &synonym) const {
    for (const auto& synonymValue : synonymValuesList) {
        if (*synonymValue.getSynonym() == synonym) {
            return synonymValue;
        }
    }
    throw std::runtime_error("Synonym not found in context");
}

bool QueryEvaluationContext::containsSynonym(const Synonym &synonym) const {
    for (const auto& synonymValue : synonymValuesList) {
        if (*synonymValue.getSynonym() == synonym) {
            return true;
        }
    }
    return false;
}

std::list<Synonym> QueryEvaluationContext::getSynonyms() const {
    std::list<Synonym> synonyms;
    for (const auto& synonymValue : synonymValuesList) {
        synonyms.push_back(*synonymValue.getSynonym());
    }
    return synonyms;
}

void QueryEvaluationContext::clearSynonymValuesList() {
    synonymValuesList.clear();
}





