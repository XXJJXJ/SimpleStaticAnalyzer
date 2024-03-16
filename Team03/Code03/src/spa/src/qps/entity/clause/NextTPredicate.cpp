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

std::string NextTPredicate::toString() const {
    return "NextT predicate";
}