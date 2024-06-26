// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "FollowsTPredicate.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/HeaderTable.h"

FollowsTPredicate::FollowsTPredicate(StatementRef lhs, StatementRef rhs) {
    if (!isValidStatementRef(lhs) || !isValidStatementRef(rhs)) {
        throw SemanticErrorException("Invalid arguments for FollowsTPredicate constructor");
    }

    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);
    addStmtRef(this->lhs);
    addStmtRef(this->rhs);
}

std::shared_ptr<BaseTable> FollowsTPredicate::getFullTable(QueryManager &qm) {
    return std::make_shared<BaseTable>(qm.getFollowT(), 2);
}

PredicateType FollowsTPredicate::getType() const {
    return PredicateType::FollowsT;
}
// ai-gen end

bool FollowsTPredicate::operator==(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const FollowsTPredicate &>(other);
    return this->lhs == castedOther.lhs && this->rhs == castedOther.rhs;
}
size_t FollowsTPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (std::hash<StatementRef>()(lhs) << 1)
        ^ (std::hash<StatementRef>()(rhs) >> 1);
}