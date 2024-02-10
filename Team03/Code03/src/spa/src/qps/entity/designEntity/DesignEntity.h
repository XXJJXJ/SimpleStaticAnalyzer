// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
#pragma once

#include <string>

class DesignEntity {
public:
    virtual ~DesignEntity() = default;
    virtual std::string getValue() const = 0;
};

// ai-gen end