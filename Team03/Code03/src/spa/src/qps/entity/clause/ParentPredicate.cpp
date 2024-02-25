// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "ParentPredicate.h"


ParentPredicate::ParentPredicate(StatementRef lhs, StatementRef rhs) {
    if (!isValidStatementRef(lhs) || !isValidStatementRef(rhs)) {
        throw SyntaxErrorException("Invalid argument for ParentPredicate constructor");
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


std::shared_ptr<BaseTable> ParentPredicate::getTable(QueryManager &qm) {
    // Step 1: Fetch all parent relationships as a BaseTable
    auto allParents = BaseTable(
            qm.getParentS(), 2); // Assuming getParentS returns data compatible with BaseTable constructor

    // Step 2: Filter based on lhs and rhs
    auto filteredParents = allParents.filter([this](const std::vector<std::shared_ptr<Entity>>& row) {
        return isValidRow(row);
    });

    // Step 3: Project to keep columns associated with a Synonym or determine a boolean result
    bool isLhsSynonym = std::holds_alternative<Synonym>(lhs);
    bool isRhsSynonym = std::holds_alternative<Synonym>(rhs);
    shared_ptr<BaseTable> resultTable = filteredParents->project({isLhsSynonym, isRhsSynonym});
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

bool ParentPredicate::isValidRow(const std::vector<std::shared_ptr<Entity>>& row) const {
    if (row.size() != 2) {
        throw QPSEvaluationException("ParentPredicate: got a row with size != 2 from PKB");
    }

    auto parentStatement = std::dynamic_pointer_cast<Statement>(row[0]);
    auto childStatement = std::dynamic_pointer_cast<Statement>(row[1]);
    if (parentStatement == nullptr || childStatement == nullptr) {
        throw QPSEvaluationException("ParentPredicate: non-statement entity in the row from PKB");
    }

    bool lhsMatch = std::holds_alternative<std::string>(lhs) && std::get<std::string>(lhs) == "_";
    bool rhsMatch = std::holds_alternative<std::string>(rhs) && std::get<std::string>(rhs) == "_";

    if (std::holds_alternative<int>(lhs)) {
        int lhsInt = std::get<int>(lhs);
        lhsMatch = parentStatement->getStatementNumber() == lhsInt;
    } else if (std::holds_alternative<Synonym>(lhs)) {
        auto lhsSynonym = std::get<Synonym>(lhs);
        lhsMatch = parentStatement->isOfType(lhsSynonym.getType());
    }

    if (std::holds_alternative<int>(rhs)) {
        int rhsInt = std::get<int>(rhs);
        rhsMatch = childStatement->getStatementNumber() == rhsInt;
    } else if (std::holds_alternative<Synonym>(rhs)) {
        auto rhsSynonym = std::get<Synonym>(rhs);
        rhsMatch = childStatement->isOfType(rhsSynonym.getType());
    }

    return lhsMatch && rhsMatch;
}

std::string ParentPredicate::toString() const {
    std::string lhsStr = std::visit(overloaded {
            [](const int val) { return std::to_string(val); },
            [](const Synonym& syn) { return syn.getName(); },
            [](const std::string& str) { return str; },
            [](const auto&) { return std::string("Unsupported Type"); }
    }, lhs);

    std::string rhsStr = std::visit(overloaded {
            [](const int val) { return std::to_string(val); },
            [](const Synonym& syn) { return syn.getName(); },
            [](const std::string& str) { return str; },
            [](const auto&) { return std::string("Unsupported Type"); }
    }, rhs);

    return "ParentPredicate " + lhsStr + " " + rhsStr;
}

// ai-gen end