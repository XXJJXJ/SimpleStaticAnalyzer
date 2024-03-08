#pragma once
#include "ColumnValidator.h"
#include <memory>
#include <string>

class IdentifierValidator : public ColumnValidator {
    std::string expectedIdentifier;

public:
    explicit IdentifierValidator(const std::string& identifier);
    bool validate(const std::shared_ptr<Entity>& entity) const override;
};
