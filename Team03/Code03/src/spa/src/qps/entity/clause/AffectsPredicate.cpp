#include "AffectsPredicate.h"

std::shared_ptr<BaseTable> AffectsPredicate::getFullTable(QueryManager &qm) {
    return std::make_shared<BaseTable>(qm.getAffects(), 2);
}

AffectsPredicate::AffectsPredicate(StatementRef lhs, StatementRef rhs) {
    if (!isValidStatementRef(lhs) || !isValidStatementRef(rhs)) {
        throw SemanticErrorException("Invalid argument for AffectsPredicate constructor");
    }

    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);
    addStmtRef(this->lhs);
    addStmtRef(this->rhs);
}

PredicateType AffectsPredicate::getType() const {
    return PredicateType::Affects;
}


bool AffectsPredicate::operator==(const AffectsPredicate &other) const {
    return this->lhs == other.lhs && this->rhs == other.rhs;
}

size_t AffectsPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (std::hash<StatementRef>()(lhs) << 1) 
            ^ (std::hash<StatementRef>()(rhs) >> 1);
}
bool AffectsPredicate::equals(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const AffectsPredicate&>(other);
    return *this == castedOther;
}