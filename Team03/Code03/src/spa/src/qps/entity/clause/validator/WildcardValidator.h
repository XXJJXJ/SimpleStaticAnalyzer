#pragma once
#include "ColumnValidator.h"
#include <memory>

class WildcardValidator : public ColumnValidator {
public:
    WildcardValidator() = default;
    bool validate(const std::shared_ptr<Entity>& entity) const override;
};
