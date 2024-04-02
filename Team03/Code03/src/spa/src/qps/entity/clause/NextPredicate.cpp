#include "NextPredicate.h"

std::shared_ptr<BaseTable> NextPredicate::getFullTable(QueryManager &qm) {
    return std::make_shared<BaseTable>(qm.getNextS(), 2);
}

NextPredicate::NextPredicate(StatementRef lhs, StatementRef rhs) {
    if (!isValidStatementRef(lhs) || !isValidStatementRef(rhs)) {
        throw SemanticErrorException("Invalid argument for NextPredicate constructor");
    }

    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);
    addStmtRef(this->lhs);
    addStmtRef(this->rhs);
}

PredicateType NextPredicate::getType() const {
    return PredicateType::Next;
}
