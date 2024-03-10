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

    return make_shared<BaseTable>(
            qm.getAssignPattern(stripWildcard(rhs), hasWildcard(rhs)), 2);
}




