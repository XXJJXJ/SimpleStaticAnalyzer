#include "NextTPredicate.h"

std::shared_ptr<BaseTable> NextTPredicate::getFullTable(QueryManager &qm) {
    return std::make_shared<BaseTable>(qm.getNextT(), 2);
}

NextTPredicate::NextTPredicate(StatementRef lhs, StatementRef rhs) {
    if (!isValidStatementRef(lhs) || !isValidStatementRef(rhs)) {
        throw SemanticErrorException("Invalid argument for NextTPredicate constructor");
    }

    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);
    addStmtRef(this->lhs);
    addStmtRef(this->rhs);
}

PredicateType NextTPredicate::getType() const {
    return PredicateType::NextT;
}

bool NextTPredicate::operator==(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const NextTPredicate&>(other);
    return this->lhs == castedOther.lhs && this->rhs == castedOther.rhs;
}
size_t NextTPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (std::hash<StatementRef>()(lhs) << 1) 
            ^ (std::hash<StatementRef>()(rhs) >> 1);
}