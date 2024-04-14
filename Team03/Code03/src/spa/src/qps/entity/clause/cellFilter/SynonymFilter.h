#pragma once
#include "CellFilter.h"
#include "qps/entity/query/Synonym.h" // Make sure this path is correct
#include <memory>

class SynonymFilter : public CellFilter {
    EntityType expectedType;

public:
    explicit SynonymFilter(const Synonym &synonym);
    bool passFilter(const std::shared_ptr<Entity> &entity) const override;
};
