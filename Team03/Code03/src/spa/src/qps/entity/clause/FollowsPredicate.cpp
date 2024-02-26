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

    if (std::holds_alternative<Synonym>(this->lhs)) {
        auto synonym = std::get<Synonym>(this->lhs);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
    }
    if (std::holds_alternative<Synonym>(this->rhs)) {
        auto synonym = std::get<Synonym>(this->rhs);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
    }
}


shared_ptr<BaseTable> FollowsPredicate::getTable(QueryManager &qm) {
    // Step 1: Fetch all follows relationships as a BaseTable
    auto allFollows = BaseTable(
            qm.getFollowS(), 2); // Assuming getFollowS returns data compatible with BaseTable constructor
    // Step 2: Filter based on lhs and rhs
    // The filtering logic will depend on the nature of lhs and rhs (integer, wildcard, synonym)
    auto filteredFollows = allFollows.filter([this](const std::vector<std::shared_ptr<Entity>>& row) {
        return isValidRow(row);
    });

    // Step 3: Project to keep columns associated with a Synonym or determine a boolean result
    bool isLhsSynonym = std::holds_alternative<Synonym>(lhs);
    bool isRhsSynonym = std::holds_alternative<Synonym>(rhs);
    shared_ptr<BaseTable> resultTable = filteredFollows->project({isLhsSynonym, isRhsSynonym});
    if (!resultTable->isBoolean()) {
        // an additional filter to drop row if all headers are the same and the values are different
        if (synonyms.size() == 2 && *synonyms[0] == *synonyms[1]) {
            resultTable = resultTable->filter([](const std::vector<std::shared_ptr<Entity>> &row) {
                return row[0] == row[1];
            });
        }
        resultTable = std::make_shared<HeaderTable>(synonyms, *resultTable);
    }
    return resultTable;
}

bool FollowsPredicate::isValidRow(const vector<shared_ptr<Entity>>& row) const {
    if (row.size() != 2) {
        throw QPSEvaluationException("FollowsPredicate: got a row with size != 2 from PKB");
    }

    bool lhsMatch = true; // Default to true for wildcard "_"
    bool rhsMatch = true; // Same as above
    auto lhsStatement = std::dynamic_pointer_cast<Statement>(row[0]);
    auto rhsStatement = std::dynamic_pointer_cast<Statement>(row[1]);
    if (lhsStatement == nullptr || rhsStatement == nullptr) {
        throw QPSEvaluationException("FollowsPredicate: got a non-statement entity in the row from PKB");
    }

    if (std::holds_alternative<int>(lhs)) {
        int lhsInt = std::get<int>(lhs);
        lhsMatch = lhsStatement->getStatementNumber() == lhsInt; // Assuming row[0] is the lhs entity and has an ID method
    } else if (std::holds_alternative<Synonym>(lhs)) {
        auto lhsSynonym = std::get<Synonym>(lhs);
        lhsMatch = lhsStatement->isOfType(lhsSynonym.getType());
    }

    if (std::holds_alternative<int>(rhs)) {
        int rhsInt = std::get<int>(rhs);
        rhsMatch = rhsStatement->getStatementNumber() == rhsInt; // Assuming row[1] is the rhs entity and has an ID method
    } else if (std::holds_alternative<Synonym>(rhs)) {
        auto rhsSynonym = std::get<Synonym>(rhs);
        rhsMatch = rhsStatement->isOfType(rhsSynonym.getType());
    }

    return lhsMatch && rhsMatch;
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
// ai-gen end