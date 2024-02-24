// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "FollowsPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/HeaderTable.h"


FollowsPredicate::FollowsPredicate(StatementRef lhs, StatementRef rhs) {
    if (!isValidStatementRef(lhs) || !isValidStatementRef(rhs)) {
        throw SyntaxErrorException("Invalid argument for FollowsPredicate constructor");
    }

    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);

    if (std::holds_alternative<Synonym>(this->lhs)) {
        auto synonym = std::get<Synonym>(lhs);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
    }
    if (std::holds_alternative<Synonym>(this->rhs)) {
        auto synonym = std::get<Synonym>(rhs);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
    }
}


shared_ptr<BaseTable> FollowsPredicate::getTable(QueryManager &qm) {
    // Step 1: Fetch all follows relationships as a BaseTable
    auto allFollows = BaseTable(
            qm.getFollowS()); // Assuming getFollowS returns data compatible with BaseTable constructor

    // Step 2: Filter based on lhs and rhs
    // The filtering logic will depend on the nature of lhs and rhs (integer, wildcard, synonym)
    auto filteredFollows = allFollows.filter([&](const std::vector<std::shared_ptr<Entity>> &row) -> bool {
        if (row.size() != 2) {
            throw QPSEvaluationException("FollowsPredicate: got a row with size != 2 from PKB");
        }

        bool lhsMatch = true; // Default to true for wildcard "_"
        bool rhsMatch = true; // Same as above

        if (std::holds_alternative<int>(lhs)) {
            int lhsInt = std::get<int>(lhs);
            auto lhsStatement = std::dynamic_pointer_cast<Statement>(row[0]);
            if (lhsStatement == nullptr) {
                throw QPSEvaluationException("FollowsPredicate: got a non-statement entity in the lhs from PKB");
            }
            lhsMatch = lhsStatement->getStatementNumber() == lhsInt; // Assuming row[0] is the lhs entity and has an ID method
        }

        if (std::holds_alternative<int>(rhs)) {
            int lhsInt = std::get<int>(rhs);
            auto lhsStatement = std::dynamic_pointer_cast<Statement>(row[1]);
            if (lhsStatement == nullptr) {
                throw QPSEvaluationException("FollowsPredicate: got a non-statement entity in the lhs from PKB");
            }
            lhsMatch = lhsStatement->getStatementNumber() == lhsInt; // Assuming row[0] is the lhs entity and has an ID method
        }

        return lhsMatch && rhsMatch;
    });

    // Step 3: Project to keep columns associated with a Synonym or determine a boolean result
    bool isLhsSynonym = std::holds_alternative<Synonym>(lhs);
    bool isRhsSynonym = std::holds_alternative<Synonym>(rhs);
    shared_ptr<BaseTable> resultTable = filteredFollows->project({isLhsSynonym, isRhsSynonym});
    if (!resultTable->isBoolean()) {
        resultTable = std::make_shared<HeaderTable>(synonyms, *resultTable);
    }
    return resultTable;
}

// ai-gen end