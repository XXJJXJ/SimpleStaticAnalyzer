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
