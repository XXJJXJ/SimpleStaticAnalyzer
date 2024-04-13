#pragma once
#include "CellFilter.h"
#include <memory>

class WildcardFilter : public CellFilter {
public:
    WildcardFilter() = default;
    bool passFilter(const std::shared_ptr<Entity> &entity) const override;
};
