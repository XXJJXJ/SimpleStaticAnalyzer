// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/b4e5ee0e-2ffc-4b9b-810c-871f71f82758
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

// ai-gen end