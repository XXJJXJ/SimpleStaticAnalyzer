// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
#include "QueryEvaluationContext.h"
#include <algorithm>

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




