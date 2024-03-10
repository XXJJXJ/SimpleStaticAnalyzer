// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/b4e5ee0e-2ffc-4b9b-810c-871f71f82758
#ifndef PROJECTIONSTRATEGY_H
#define PROJECTIONSTRATEGY_H

#include <memory>
#include <list>
#include "Strategy.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/BooleanTable.h"

class ProjectionStrategy : public Strategy {
public:
    explicit ProjectionStrategy(vector<std::shared_ptr<Synonym>> synonyms);
    void execute(QueryEvaluationContext &context) override;

private:
    vector<std::shared_ptr<Synonym>> targetSynonyms;
    vector<SynonymPtrSet> groupTargetSynonyms(QueryEvaluationContext &context) const;

    vector<shared_ptr<HeaderTable>> getProjectedTables(QueryEvaluationContext &context);
};

#endif // PROJECTIONSTRATEGY_H

// ai-gen end