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
    // Cast to assignSyn to EntityRef
    EntityRef assignSynRef = this->assignSyn;
    addEntityRef(assignSynRef);
    addEntityRef(this->lhs);
}

std::shared_ptr<BaseTable> AssignPatternPredicate::getFullTable(QueryManager &qm) {
    // Step 1: get all possible LHS (arg1)
    vector<shared_ptr<Entity>> allPossibleLhs;
    if (holds_alternative<string>(lhs) && get<string>(lhs) != WILDCARD) {
        // We don't have access to the internal of PKB here, so we can only create a new variable with the same name
        allPossibleLhs.push_back(make_shared<Variable>(get<string>(lhs)));
    } else {
        allPossibleLhs = qm.getAllEntitiesByType(EntityType::Variable);
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
    return make_shared<BaseTable>(table);
}




