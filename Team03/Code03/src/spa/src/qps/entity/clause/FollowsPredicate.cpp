// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "FollowsPredicate.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/HeaderTable.h"

FollowsPredicate::FollowsPredicate(StatementRef lhs, StatementRef rhs) {
    if (!isValidStatementRef(lhs) || !isValidStatementRef(rhs)) {
        throw SemanticErrorException("Invalid argument for FollowsPredicate constructor");
    }

    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);
    addStmtRef(this->lhs);
    addStmtRef(this->rhs);
}

std::shared_ptr<BaseTable> FollowsPredicate::getFullTable(QueryManager &qm) {
    return make_shared<BaseTable>(qm.getFollowS(), 2);
}

PredicateType FollowsPredicate::getType() const {
    return PredicateType::Follows;
}
// ai-gen end

bool FollowsPredicate::operator==(const FollowsPredicate &other) const {
    return this->lhs == other.lhs && this->rhs == other.rhs;
}
size_t FollowsPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (std::hash<StatementRef>()(lhs) << 1) 
            ^ (std::hash<StatementRef>()(rhs) >> 1);
}
bool FollowsPredicate::equals(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const FollowsPredicate&>(other);
    return *this == castedOther;
}