
#pragma once
#include "ColumnValidator.h"
#include "qps/entity/query/Synonym.h" // Make sure this path is correct
#include <memory>

class SynonymValidator : public ColumnValidator {
    EntityType expectedType;

public:
    explicit SynonymValidator(const Synonym& synonym);
    bool validate(const std::shared_ptr<Entity>& entity) const override;
};
