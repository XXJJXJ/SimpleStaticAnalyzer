#include "AssignPatternPredicate.h"

AssignPatternPredicate::AssignPatternPredicate(Synonym assignSyn, EntityRef lhs, std::string rhs) 
		: assignSyn(std::move(assignSyn)), lhs(std::move(lhs)), rhs(std::move(rhs)) {
    bool isValidAssignSyn = this->assignSyn.getType() == EntityType::Assign;
    bool isLhsValid = isValidEntityRef(this->lhs);
    if (holds_alternative<Synonym>(this->lhs)) {
        auto synonym = get<Synonym>(this->lhs);
        isLhsValid &= synonym.getType() == EntityType::Variable;
    }
	if (!isValidAssignSyn || !isLhsValid) {
		throw SemanticErrorException("Invalid argument for AssignPatternPredicate constructor");
	}

    synonyms.push_back(make_shared<Synonym>(this->assignSyn));
    if (holds_alternative<Synonym>(this->lhs)) {
        auto synonym = get<Synonym>(this->lhs);
        synonyms.push_back(make_shared<Synonym>(synonym));
    }
}

shared_ptr<BaseTable> AssignPatternPredicate::getTable(QueryManager &qm) {
    // Step 1: get all possible LHS (arg1)
    vector<shared_ptr<Entity>> allPossibleLhs;
    if (holds_alternative<string>(lhs) && get<string>(lhs) != WILDCARD) {

        // TODO: Ask PKB to support querying by variable name and refactor this
        allPossibleLhs.push_back(make_shared<Variable>(get<string>(lhs)));

    } else {
        // TODO: Ask PKB to return Entity and refactor this
        for (auto& variable : qm.getAllEntitiesByType(EntityType::Variable)) {
            // cast to shared_ptr<Entity>
            allPossibleLhs.push_back(variable);
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



