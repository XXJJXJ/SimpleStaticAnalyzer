
#pragma once
#include "ColumnValidator.h" // Ensure this path is correct
#include "common/Statement.h" // Ensure this path is correct
#include <memory>

class StatementNumberValidator : public ColumnValidator {
    int expectedNumber;

public:
    explicit StatementNumberValidator(int expectedNumber);
    bool validate(const std::shared_ptr<Entity>& entity) const override;
};
