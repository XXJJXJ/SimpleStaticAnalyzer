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
    bool isRhsValid = isValidRhs(this->rhs);    // TODO: Get rid of this check, this should be in query validator
	if (!isValidAssignSyn || !isLhsValid || !isRhsValid) {
		throw SemanticErrorException("Invalid argument for AssignPatternPredicate constructor");
	}
    // Cast to assignSyn to EntityRef
    EntityRef assignSynRef = this->assignSyn;
    addEntityRef(assignSynRef);
    addEntityRef(this->lhs);
}


// Allowed RHS expressions:
// - Wildcard _
// - Expression for exact match(e.g. "x*y")
// - Expression for partial match(e.g._"x*y"_)
// TODO: This shouldn't be here, this should be in query validator.
bool AssignPatternPredicate::isValidRhs(const std::string& rhs) {
    size_t len = rhs.size();
    return rhs == "_" ||
           len > 1 && rhs[0] != '"' && rhs[len - 1] != '"' ||
           len > 4 && rhs[0] == '_' && rhs[1] == '"' && rhs[len - 2] == '"' && rhs[len - 1] == '_';
}

std::shared_ptr<BaseTable> AssignPatternPredicate::getFullTable(QueryManager &qm) {
    // TODO: move this logic to PKB, and we need a interface that takes in (expr, hasWildcard), and return a
    //  vector<vector<shared_ptr<Entity>>>, where each row contains (assignStmt, variable).
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




