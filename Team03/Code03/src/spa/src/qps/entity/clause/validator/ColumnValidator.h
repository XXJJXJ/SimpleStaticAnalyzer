#pragma once

#include <memory>
#include "common/Entity.h" // Make sure this path is correct according to your project structure

/**
 * Abstract class that represents a column validator. A column validator is used to validate a cell in a row resulted
 * from PKB query. It is used to filter out rows that do not satisfy the validation criteria.
 */
class ColumnValidator {
public:
    virtual ~ColumnValidator() = default;

    // Pure virtual function that must be overridden by subclasses
    // Returns true if the entity passes the validation criteria, false otherwise
    virtual bool validate(const std::shared_ptr<Entity>& entity) const = 0;
};
