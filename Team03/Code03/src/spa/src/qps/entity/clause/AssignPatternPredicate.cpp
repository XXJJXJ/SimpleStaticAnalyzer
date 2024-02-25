#include "AssignPatternPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"

AssignPatternPredicate::AssignPatternPredicate(Synonym assignSyn, EntityRef lhs, std::string rhs) 
		: assignSyn(std::move(assignSyn)), lhs(std::move(lhs)), rhs(std::move(rhs)) {
    bool isValidAssignSyn = this->assignSyn.getType() == EntityType::Assign;
    bool isLhsValid = isValidEntityRef(this->lhs);
    if (holds_alternative<Synonym>(this->lhs)) {
        auto synonym = get<Synonym>(this->lhs);
        isLhsValid &= synonym.getType() == EntityType::Variable;
    }
    bool isRhsValid = isValidRhs(this->rhs);
	if (!isValidAssignSyn || !isLhsValid || !isRhsValid) {
		throw SyntaxErrorException("Invalid argument for AssignPatternPredicate constructor");
	}

    synonyms.push_back(make_shared<Synonym>(this->assignSyn));
    if (holds_alternative<Synonym>(this->lhs)) {
        auto synonym = get<Synonym>(this->lhs);
        synonyms.push_back(make_shared<Synonym>(synonym));
    }
}



bool AssignPatternPredicate::isValidRow(const vector<std::shared_ptr<Entity>> &row) const {
    return false;
}

// Allowed RHS expressions:
// - Wildcard _
// - Expression for exact match(e.g. "x*y")
// - Expression for partial match(e.g._"x*y"_)
bool AssignPatternPredicate::isValidRhs(const std::string& rhs) {
    size_t len = rhs.size();
    return rhs == "_" ||
           len > 1 && rhs[0] != '"' && rhs[len - 1] != '"' ||
           len > 4 && rhs[0] == '_' && rhs[1] == '"' && rhs[len - 2] == '"' && rhs[len - 1] == '_';
}



shared_ptr<BaseTable> AssignPatternPredicate::getTable(QueryManager &qm) {
    // Step 1: get all possible LHS (arg1)
    vector<shared_ptr<Entity>> allPossibleLhs;
    if (holds_alternative<string>(lhs) && get<string>(lhs) != WILDCARD) {

        // TODO: Ask PKB to support querying by variable name and refactor this
        allPossibleLhs.push_back(make_shared<Variable>(get<string>(lhs)));

    } else {
        // TODO: Ask PKB to return Entity and refactor this
        for (auto& variable : qm.getAllVariables()) {
            // cast to shared_ptr<Entity>
            allPossibleLhs.push_back(static_pointer_cast<Entity>(variable));
        }
    }

    // Step 2: construct the table
    BaseTable table;
    table.setColumnCount(2);
    for (auto& arg : allPossibleLhs) {
        auto assignments = qm.getAssignPattern(arg->getName(), stripWildcard(rhs), hasWildcard(rhs));
        for (auto& assignment : assignments) {
            // Only need to filter arg
            if (arg->isOfType(EntityType::Variable)) {
                table.addRow(TableRow({static_pointer_cast<Entity>(assignment), arg}));
            }
        }
    }

    // Step 3: project to keep columns associated with a Synonym or determine a boolean result
    bool isAssignSynonym = true;
    bool isLhsSynonym = holds_alternative<Synonym>(lhs);
    shared_ptr<BaseTable> resultTable = table.project({isAssignSynonym, isLhsSynonym});

    // Result table can't be boolean, as assign must be synonym
    resultTable = make_shared<HeaderTable>(synonyms, *resultTable);
    return resultTable;
}



