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
    return make_shared<BaseTable>(
            qm.getAssignPattern(stripWildcard(rhs), hasWildcard(rhs)), 2);
}




