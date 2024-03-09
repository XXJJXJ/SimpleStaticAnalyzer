
#pragma once
#include "CellFilter.h" // Ensure this path is correct
#include "common/Statement.h" // Ensure this path is correct
#include <memory>

class StatementNumberFilter : public CellFilter {
    int expectedNumber;

public:
    explicit StatementNumberFilter(int expectedNumber);
    bool passFilter(const std::shared_ptr<Entity>& entity) const override;
};
