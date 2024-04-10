// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "ParentPredicate.h"


ParentPredicate::ParentPredicate(StatementRef lhs, StatementRef rhs) {
    if (!isValidStatementRef(lhs) || !isValidStatementRef(rhs)) {
        throw SemanticErrorException("Invalid argument for ParentPredicate constructor");
    }

    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);
    addStmtRef(this->lhs);
    addStmtRef(this->rhs);
}

std::shared_ptr<BaseTable> ParentPredicate::getFullTable(QueryManager &qm) {
    return std::make_shared<BaseTable>(qm.getParentS(), 2);
}

PredicateType ParentPredicate::getType() const {
    return PredicateType::Parent;
}
// ai-gen end
bool ParentPredicate::operator==(const ParentPredicate &other) const {
    return this->lhs == other.lhs && this->rhs == other.rhs;
}
size_t ParentPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (std::hash<StatementRef>()(lhs) << 1) 
            ^ (std::hash<StatementRef>()(rhs) >> 1);
}
bool ParentPredicate::equals(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const ParentPredicate&>(other);
    return *this == castedOther;
}