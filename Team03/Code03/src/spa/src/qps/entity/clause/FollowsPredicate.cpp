// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "FollowsPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"
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

std::string FollowsPredicate::toString() const {
    // Temp implementation for debugging, TODO: replace with proper implementation
    // get string presentation of lhs and rhs based on their types
    std::string lhsStr;
    std::string rhsStr;
    if (std::holds_alternative<int>(lhs)) {
        lhsStr = std::to_string(std::get<int>(lhs));
    } else if (std::holds_alternative<Synonym>(lhs)) {
        lhsStr = std::get<Synonym>(lhs).getName();
    } else {
        lhsStr = "_";
    }
    if (std::holds_alternative<int>(rhs)) {
        rhsStr = std::to_string(std::get<int>(rhs));
    } else if (std::holds_alternative<Synonym>(rhs)) {
        rhsStr = std::get<Synonym>(rhs).getName();
    } else {
        rhsStr = "_";
    }
    return "FollowsPredicate " + lhsStr + " " + rhsStr;
}

std::shared_ptr<BaseTable> FollowsPredicate::getFullTable(QueryManager &qm) {
    return make_shared<BaseTable>(qm.getFollowS(), 2);
}
// ai-gen end