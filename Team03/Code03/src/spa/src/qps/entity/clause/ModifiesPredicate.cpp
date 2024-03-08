// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "ModifiesPredicate.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/HeaderTable.h"

ModifiesPredicate::ModifiesPredicate(ModifiesLhsRef lhs, EntityRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidStatementOrEntityRef(this->lhs) || !isValidVariable(this->rhs)) {
        throw SemanticErrorException("Invalid arguments for ModifiesPredicate constructor");
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

shared_ptr<BaseTable> ModifiesPredicate::getTable(QueryManager& qm) {
    // Step 1: Fetch all follows relationships as a BaseTable
    auto allModifies = BaseTable(qm.getModifyByType(EntityType::Stmt), 2); 

    // Step 2: Filter based on lhs and rhs
    // The filtering logic will depend on the nature of lhs and rhs (integer, wildcard, synonym)
    auto filteredModifies = allModifies.filter([this](const std::vector<std::shared_ptr<Entity>>& row) { 
        return isValidRow(row); 
    });

    // Step 3: Project to keep columns associated with a Synonym or determine a boolean result
    bool isLhsSynonym = std::holds_alternative<Synonym>(lhs);
    bool isRhsSynonym = std::holds_alternative<Synonym>(rhs);
    shared_ptr<BaseTable> resultTable = filteredModifies->project({isLhsSynonym, isRhsSynonym});
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

bool ModifiesPredicate::isValidRow(const vector<shared_ptr<Entity>>& row) const {
    if (row.size() != 2) {
        throw QPSEvaluationException("ModifiesPredicate: got a row with size != 2 from PKB");
    }

    bool lhsMatch = true; // Default to true for wildcard "_"
    bool rhsMatch = true; // Same as above
    auto lhsStatement = std::dynamic_pointer_cast<Statement>(row[0]);
    auto rhsVariable = std::dynamic_pointer_cast<Variable>(row[1]);
    if (lhsStatement == nullptr || rhsVariable == nullptr) {
        throw QPSEvaluationException(
            "ModifiesPredicate: got a non-statement entity in the row from PKB");
    }

    if (std::holds_alternative<int>(lhs)) {
        int lhsInt = std::get<int>(lhs);
        lhsMatch = lhsStatement->getStatementNumber() == lhsInt; // Assuming row[0] is the lhs entity and has an ID method
    } else if (std::holds_alternative<Synonym>(lhs)) {
        auto lhsSynonym = std::get<Synonym>(lhs);
        lhsMatch = lhsStatement->isOfType(lhsSynonym.getType());
    }

    if (std::holds_alternative<std::string>(rhs)) {
        std::string rhsString = std::get<std::string>(rhs);
        rhsMatch = rhsString == "_" || rhsVariable->getName() == rhsString; // Assuming row[1] is the rhs entity and has an ID method
    } else if (std::holds_alternative<Synonym>(rhs)) {
        auto rhsSynonym = std::get<Synonym>(rhs);
        rhsMatch = rhsVariable->isOfType(rhsSynonym.getType());
    }

    return lhsMatch && rhsMatch;
}

// ai-gen end