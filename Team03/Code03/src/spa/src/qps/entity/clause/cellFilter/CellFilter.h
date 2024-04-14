#pragma once

#include <memory>
#include "common/Entity.h" // Make sure this path is correct according to your project structure

/**
 * Abstract class that represents a cell filter. A cell filter is used to filter a cell in a row resulted
 * from PKB query. It is used to filter out row that do not satisfy the validation criteria.
 */
class CellFilter {
public:
    virtual ~CellFilter() = default;

    // Pure virtual function that must be overridden by subclasses
    // Returns true if the entity passes the validation criteria, false otherwise
    [[nodiscard]] virtual bool passFilter(const std::shared_ptr<Entity> &entity) const = 0;

};
