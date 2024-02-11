// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
#include "SynonymValues.h"
#include "common/Entity.h"

void SynonymValues::addValue(const std::shared_ptr<Entity>& value) {
    values.push_back(value);
}

const std::vector<std::shared_ptr<Entity>>& SynonymValues::getValues() const {
    return values;
}


// ai-gen end

vector<string> SynonymValues::toStringList() const {
    vector<string> result;
    result.reserve(values.size());
for (const auto& value : values) {
        result.push_back(value->getName());
    }
    return result;
}