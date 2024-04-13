#pragma once
#include "CellFilter.h"
#include <memory>
#include <string>

class IdentifierFilter : public CellFilter {
    std::string expectedIdentifier;

public:
    explicit IdentifierFilter(const std::string &identifier);
    bool passFilter(const std::shared_ptr<Entity> &entity) const override;
};
