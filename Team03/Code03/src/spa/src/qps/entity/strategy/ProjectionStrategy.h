#ifndef PROJECTIONSTRATEGY_H
#define PROJECTIONSTRATEGY_H

#include <memory>
#include <list>
#include "Strategy.h"

class ProjectionStrategy : public Strategy {
public:
    explicit ProjectionStrategy(std::shared_ptr<Synonym> synonym);
    void execute(QueryEvaluationContext &context) override;

private:
    std::shared_ptr<Synonym> targetSynonym;
};

#endif // PROJECTIONSTRATEGY_H

