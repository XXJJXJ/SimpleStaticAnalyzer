// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
#pragma once

#include "qps/entity/query/Synonym.h"
#include "common/Entity.h"
#include <vector>
#include <memory>

// Represents a list of possible values for a synonym.
class SynonymValues {
private:
    shared_ptr<Synonym> synonym;
    std::vector<std::shared_ptr<Entity>> values;

public:
    explicit SynonymValues(const shared_ptr<Synonym> &syn) : synonym(syn) {}
    void addValue(const std::shared_ptr<Entity>& value);
    [[nodiscard]] const std::vector<std::shared_ptr<Entity>>& getValues() const;
    [[nodiscard]] shared_ptr<Synonym> getSynonym() const { return synonym; }
    [[nodiscard]] vector<string> toStringList() const;
    bool operator==(const SynonymValues &rhs) const;
};
// ai-gen end