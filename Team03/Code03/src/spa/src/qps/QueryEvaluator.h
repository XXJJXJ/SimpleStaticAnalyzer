// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/cc725a19-b2cb-4541-9910-0b2b77365e00
#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H

#include <string>
#include <memory>
#include "qps/entity/evaluation/QueryEvaluationContext.h"
#include "qps/entity/query/Query.h"

class QueryEvaluator {
private:
    std::shared_ptr<QueryEvaluationContext> context;
    std::vector<std::shared_ptr<Strategy>> strategies;

public:
    QueryEvaluator();
    void setStrategies(const std::vector<std::shared_ptr<Strategy>>& strategies);
    std::vector<std::string> evaluate(const std::shared_ptr<Query>& query);
    std::shared_ptr<QueryEvaluationContext> getContext() const;
};


#endif //SPA_QUERYEVALUATOR_H

// ai-gen end