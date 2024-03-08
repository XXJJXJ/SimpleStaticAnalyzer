// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#ifndef PARENTPREDICATE_H
#define PARENTPREDICATE_H

#include "Predicate.h"
#include "qps/entity/evaluation/HeaderTable.h"
#include "PredicateUtils.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include <memory>

class ParentPredicate : public Predicate {
private:
    StatementRef lhs;
    StatementRef rhs;

public:
    ParentPredicate(StatementRef lhs, StatementRef rhs);
    std::shared_ptr<BaseTable> getTable(QueryManager &qm) override;
    std::string toString() const override;
};

#endif // PARENTPREDICATE_H


// ai-gen end