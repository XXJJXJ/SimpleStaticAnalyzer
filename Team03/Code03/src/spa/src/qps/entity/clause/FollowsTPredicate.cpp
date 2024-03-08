// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "FollowsTPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/HeaderTable.h"

FollowsTPredicate::FollowsTPredicate(StatementRef lhs, StatementRef rhs) {
    if (!isValidStatementRef(lhs) || !isValidStatementRef(rhs)) {
        throw SemanticErrorException("Invalid arguments for FollowsTPredicate constructor");
    }

    this->lhs = std::move(lhs);
    this->validators.push_back(getValidatorForStatementRef(this->lhs));
    this->rhs = std::move(rhs);
    this->validators.push_back(getValidatorForStatementRef(this->rhs));

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
    auto allFollowsT = BaseTable(qm.getFollowT(), 2);

    //Step 2: Filter based on lhs and rhs
    auto filteredFollowsT = allFollowsT.filter([this](const std::vector<std::shared_ptr<Entity>>& row) {
        return isValidRow(row);
    });

    //Step 3: Project to keep columns associated with a Synonym or determine boolean result
    bool isLhsSynonym = std::holds_alternative<Synonym>(lhs);
    bool isRhsSynonym = std::holds_alternative<Synonym>(rhs);

    shared_ptr<BaseTable> resultTable = filteredFollowsT->project({isLhsSynonym, isRhsSynonym});
    if(!resultTable->isBoolean()) {
        if (synonyms.size() == 2 && *synonyms[0] == *synonyms[1]) {
            resultTable = resultTable->filter([](const std::vector<std::shared_ptr<Entity>> &row) {
                return row[0] == row[1];
            });
        }
        resultTable = std::make_shared<HeaderTable>(synonyms, *resultTable);
    }
    return resultTable;
}


// ai-gen end
