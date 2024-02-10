// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
#pragma once

#include "qps/entity/query/Synonym.h"
#include "qps/entity/designEntity/DesignEntity.h"
#include <vector>
#include <memory>

class SynonymValues {
private:
    Synonym synonym;
    std::vector<std::shared_ptr<DesignEntity>> values;

public:
    SynonymValues(const Synonym& syn) : synonym(syn) {}
    void addValue(const std::shared_ptr<DesignEntity>& value);
    const std::vector<std::shared_ptr<DesignEntity>>& getValues() const;
    Synonym getSynonym() const { return synonym; }
};
// ai-gen end