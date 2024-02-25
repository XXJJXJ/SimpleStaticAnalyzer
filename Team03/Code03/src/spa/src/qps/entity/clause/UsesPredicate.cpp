// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "UsesPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/HeaderTable.h"

UsesPredicate::UsesPredicate(UsesLhsRef lhs, EntityRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidUsesLhsRef(this->lhs) || !isValidVariable(this->rhs)) {
        throw SyntaxErrorException("Invalid arguments for UsesPredicate constructor");
    }

    if (std::holds_alternative<Synonym>(this->lhs)) {
        auto synonym = std::get<Synonym>(this->lhs);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
    }
    if (std::holds_alternative<Synonym>(this->rhs)) {
        auto synonym = std::get<Synonym>(this->rhs);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
    }
}

shared_ptr<BaseTable> UsesPredicate::getTable(QueryManager& qm) {
    // Step 1: Fetch all follows relationships as a BaseTable
    auto allUses =
        BaseTable(qm.getUseAll(),
                  2); // Assuming getFollowS returns data compatible with BaseTable constructor

    // Step 2: Filter based on lhs and rhs
    // The filtering logic will depend on the nature of lhs and rhs (integer, wildcard, synonym)
    auto filteredUses = allUses.filter(
        [this](const std::vector<std::shared_ptr<Entity>>& row) { return isValidRow(row); });

    // Step 3: Project to keep columns associated with a Synonym or determine a boolean result
    bool isLhsSynonym = std::holds_alternative<Synonym>(lhs);
    bool isRhsSynonym = std::holds_alternative<Synonym>(rhs);
    shared_ptr<BaseTable> resultTable = filteredUses->project({isLhsSynonym, isRhsSynonym});
    if (!resultTable->isBoolean()) {
        resultTable = std::make_shared<HeaderTable>(synonyms, *resultTable);
    }
    return resultTable;
}

bool UsesPredicate::isValidRow(const vector<shared_ptr<Entity>>& row) const {
    if (row.size() != 2) {
        throw QPSEvaluationException("UsesPredicate: got a row with size != 2 from PKB");
    }

    bool lhsMatch = true; // Default to true for wildcard "_"
    bool rhsMatch = true; // Same as above
    auto lhsStatement = std::dynamic_pointer_cast<Statement>(row[0]);
    auto rhsExpression = std::dynamic_pointer_cast<Expression>(row[1]);
    if (lhsStatement == nullptr || rhsExpression == nullptr) {
        throw QPSEvaluationException(
            "UsesPredicate: got a non-statement entity in the row from PKB");
    }

    if (std::holds_alternative<int>(lhs)) {
        int lhsInt = std::get<int>(lhs);
        lhsMatch = lhsStatement->getStatementNumber() ==
                   lhsInt; // Assuming row[0] is the lhs entity and has an ID method
    } else if (std::holds_alternative<Synonym>(lhs)) {
        auto lhsSynonym = std::get<Synonym>(lhs);
        lhsMatch = lhsStatement->isOfType(lhsSynonym.getType());
    } else if (std::holds_alternative<std::string>(lhs)) {
        std::string lhsString = std::get<std::string>(lhs);
        lhsMatch = lhsStatement->getName() == lhsString;
    }

    if (std::holds_alternative<std::string>(rhs)) {
        std::string rhsString = std::get<std::string>(rhs);
        rhsMatch = rhsString == "_" || rhsExpression->getName() == rhsString; // Assuming row[1] is the rhs entity and has an ID method
    } else if (std::holds_alternative<Synonym>(rhs)) {
        auto rhsSynonym = std::get<Synonym>(rhs);
        rhsMatch = rhsExpression->isOfType(rhsSynonym.getType());
    }

    return lhsMatch && rhsMatch;
}

// ai-gen end