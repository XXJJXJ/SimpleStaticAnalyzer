// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
#include "SynonymValues.h"

void SynonymValues::addValue(const std::shared_ptr<DesignEntity>& value) {
    values.push_back(value);
}

const std::vector<std::shared_ptr<DesignEntity>>& SynonymValues::getValues() const {
    return values;
}
// ai-gen end