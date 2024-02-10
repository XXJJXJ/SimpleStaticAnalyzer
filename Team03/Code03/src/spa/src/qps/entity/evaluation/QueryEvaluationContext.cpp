// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
#include "QueryEvaluationContext.h"
#include <algorithm>

void QueryEvaluationContext::addSynonymValues(const SynonymValues& synonymValues) {
    synonymValuesList.push_back(synonymValues);
}

SynonymValues QueryEvaluationContext::getSynonymValues(const Synonym& synonym) const {
    auto it = std::find_if(synonymValuesList.begin(), synonymValuesList.end(),
                           [&synonym](const SynonymValues& sv) { return sv.getSynonym().getName() == synonym.getName(); });
    if (it != synonymValuesList.end()) {
        return *it;
    }
    // Return an empty SynonymValues object if not found.
    // This requires a default constructor or another method to handle this case.
    return SynonymValues(Synonym(DesignEntityType::Statement, "")); // Example default, adjust as needed.
}
// ai-gen end