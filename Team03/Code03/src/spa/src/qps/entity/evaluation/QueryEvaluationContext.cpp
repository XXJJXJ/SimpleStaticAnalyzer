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

string QueryEvaluationContext::resultToString() const {
    // ensures that there's only one synonym list left
    // prompt: https://chat.openai.com/share/b8694b03-2e9e-465e-a3fb-e31d4fbe079a
    if (synonymValuesList.size() != 1) {
        throw std::runtime_error("There should be exactly one synonym list left");
    }
    vector<string> result = synonymValuesList.front().toStringList();

    // ai-gen start(gpt, 0, e)
    std::stringstream ss;
    for(size_t i = 0; i < result.size(); ++i) {
        ss << result[i];
        if (i != result.size() - 1) { // To avoid adding a comma after the last element
            ss << ", ";
        }
    }
    // ai-gen end

    return ss.str();
}




