// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#ifndef PARENTTPREDICATE_H
#define PARENTTPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"
#include "qps/entity/evaluation/HeaderTable.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/spa_exception/QPSEvaluationException.h"


class Strategy;

class ParentTPredicate : public Predicate {
private:
    StatementRef lhs; // Ancestor statement reference
    StatementRef rhs; // Descendant statement reference
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;
public:
    ParentTPredicate(StatementRef lhs, StatementRef rhs);
    ~ParentTPredicate() override = default;
    std::string toString() const override;

};

#endif // PARENTTPREDICATE_H

// ai-gen end