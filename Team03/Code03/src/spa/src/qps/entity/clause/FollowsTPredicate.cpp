// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "FollowsTPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/HeaderTable.h"

FollowsTPredicate::FollowsTPredicate(StatementRef lhs, StatementRef rhs) {
    if (!isValidStatementRef(lhs) || !isValidStatementRef(rhs)) {
        throw SyntaxErrorException("Invalid arguments for FollowsTPredicate constructor");
    }

    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);

    if (std::holds_alternative<Synonym>(this->lhs)) {
        auto synonym = std::get<Synonym>(this->lhs);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
    }
    if (std::holds_alternative<Synonym>(this->rhs)) {
        auto synonym = std::get<Synonym>(this->rhs);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
    }
}

std::shared_ptr<BaseTable> FollowsTPredicate::getTable(QueryManager &qm) {
    // Step 1: Fetch all followsT relationships as BaseTable
    auto allFollows = BaseTable(qm.getFollowT(), 2);

    //Step 2: Filter based on lhs and rhs
    auto filteredFollowsT = allFollows.filter([this](const std::vector<std::shared_ptr<Entity>>& row) {
        return isValidRow(row);
    });

    //Step 3: Project to keep columns associated with a Synonym or determine boolean result
    bool isLhsSynonym = std::holds_alternative<Synonym>(lhs);
    bool isRhsSynonym = std::holds_alternative<Synonym>(rhs);

    shared_ptr<BaseTable> resultTable = filteredFollowsT->project({isLhsSynonym, isRhsSynonym});
    if(!resultTable->isBoolean()) {
        resultTable = std::make_shared<HeaderTable>(synonyms, *resultTable)
    }
    return resultTable;
}

bool FollowsTPredicate::isValidRow(const std::vector<std::shared_ptr<Entity>> &row) const {
    if (row.size() != 2) {
        throw QPSEvaluationException("FollowsTPredicate: got a row with size != 2 from PKB");
    }
    bool lhsMatch = true; // Default to true for wildcard "-"
    bool rhsMatch = true; // Same as above
    auto lhsStatement = std::dynamic_pointer_cast<Statement>(row[0]);
    auto rhsStatement = std::dynamic_pointer_cast<Statement>(row[1]);
    if (lhsStatement == nullptr || rhsStatement) {
        throw QPSEvaluationException("FollowsTPredicate: got a non-statement entity in the row from PKB");
    }

    if (std::holds_alternative<int>(lhs)) {
        int lhsInt = std::get<int>(lhs);
        lhsMatch = lhsStatement->getStatementNumber() == lhsInt;
    } else if (std::holds_alternative<Synonym>(lhs)) {
        auto lhsSynonym = std::get<Synonym>(lhs);
        lhsMatch = lhsStatement->isOfType(lhsSynonym.getType());
    }

    if (std::holds_alternative<int>(rhs)) {
        int rhsInt = std::get<int>(rhs);
        rhsMatch = rhsStatement->getStatementNumber() == rhsInt;
    } else if (std::holds_alternative<Synonym>(rhs)) {
        auto rhsSynonym = std::get<Synonym>(rhs);
        rhsMatch = rhsStatement->isOfType(rhsSynonym.getType());
    }

    return lhsMatch && rhsMatch;
}

// ai-gen end