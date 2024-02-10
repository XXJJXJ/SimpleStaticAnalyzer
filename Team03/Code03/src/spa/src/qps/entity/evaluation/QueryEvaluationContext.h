// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
#pragma once

#include "SynonymValues.h"
#include <list>

class QueryEvaluationContext {
private:
    std::list<SynonymValues> synonymValuesList;

public:
    void addSynonymValues(const SynonymValues& synonymValues);
    SynonymValues getSynonymValues(const Synonym& synonym) const;
};
// ai-gen end