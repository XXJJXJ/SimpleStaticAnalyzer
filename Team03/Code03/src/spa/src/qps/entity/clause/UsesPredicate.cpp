// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "UsesPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/HeaderTable.h"

UsesPredicate::UsesPredicate(ProcAndStmtRef lhs, EntityRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidProcAndStmtRef(this->lhs) || !isValidVariable(this->rhs)) {
        throw SemanticErrorException("Invalid arguments for UsesPredicate constructor");
    }

    this->validators.push_back(getValidatorForProcAndStmtRef(this->lhs));
    this->validators.push_back(getValidatorForEntityRef(this->rhs));

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
                      2);
    // Assuming getFollowS returns data compatible with BaseTable constructor
    int count = 0;
    for (auto row: allUses.getRows()) {
        if (row.getValues()[0]->getName() == "3") {
            count++;
        }
    }

    // Step 2: Filter based on lhs and rhs
    // The filtering logic will depend on the nature of lhs and rhs (integer, wildcard, synonym)
    auto filteredUses = allUses.filter(
            [this](const std::vector<std::shared_ptr<Entity>>& row) { return isValidRow(row); });

    // Step 3: Project to keep columns associated with a Synonym or determine a boolean result
    bool isLhsSynonym = std::holds_alternative<Synonym>(lhs);
    bool isRhsSynonym = std::holds_alternative<Synonym>(rhs);
    shared_ptr<BaseTable> resultTable = filteredUses->project({isLhsSynonym, isRhsSynonym});
    if (!resultTable->isBoolean()) {
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