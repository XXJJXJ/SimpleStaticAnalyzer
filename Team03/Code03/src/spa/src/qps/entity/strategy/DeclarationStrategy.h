#pragma once

#include <vector>
#include "qps/entity/query/Synonym.h"
#include "Strategy.h"
#include "qps/entity/evaluation/QueryEvaluationContext.h"

class DeclarationStrategy : public Strategy {
private:
    std::vector<shared_ptr<Synonym>> synonyms;

public:
    explicit DeclarationStrategy(const std::vector<shared_ptr<Synonym>>& synonyms);
    void execute(QueryEvaluationContext &context) override;

    static vector<shared_ptr<Entity>> getEntitiesByType(EntityType entityType, QueryManager &queryManager);
};
