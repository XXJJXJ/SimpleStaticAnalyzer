// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "ParentTPredicate.h"

ParentTPredicate::ParentTPredicate(StatementRef lhs, StatementRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidStatementRef(this->lhs) || !isValidStatementRef(this->rhs)) {
        throw SemanticErrorException("Invalid arguments for ParentTPredicate constructor");
    }
    addStmtRef(this->lhs);
    addStmtRef(this->rhs);
}



std::shared_ptr<BaseTable> ParentTPredicate::getFullTable(QueryManager &qm) {
    return std::make_shared<BaseTable>(qm.getParentT(), 2);
}

PredicateType ParentTPredicate::getType() const {
    return PredicateType::ParentT;
}
// ai-gen end
bool ParentTPredicate::operator==(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const ParentTPredicate&>(other);
    return this->lhs == castedOther.lhs && this->rhs == castedOther.rhs;
}
size_t ParentTPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (std::hash<StatementRef>()(lhs) << 1) 
            ^ (std::hash<StatementRef>()(rhs) >> 1);
}