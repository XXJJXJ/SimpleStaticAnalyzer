#include "AssignPatternPredicate.h"
#include "common/spa_exception/SemanticErrorException.h"
#include "common/spa_exception/SyntaxErrorException.h"

AssignPatternPredicate::AssignPatternPredicate(Synonym assignSyn, EntityRef lhs, std::string rhs) 
		: assignSyn(std::move(assignSyn)), lhs(std::move(lhs)), rhs(std::move(rhs)) {
	if (!isValidAssignSyn(this->assignSyn) || !isValidLhs(this->lhs) || !isValidRhs(this->rhs)) {
		throw SyntaxErrorException("Invalid argument for AssignPatternPredicate constructor");
	}
}

bool AssignPatternPredicate::isValidAssignSyn(const Synonym& assignSyn) {
	return assignSyn.getType() == EntityType::Assign;
}

bool AssignPatternPredicate::isValidLhs(const EntityRef& lhs) {
	return std::visit(overloaded{
			[](const Synonym& syn) { return syn.getType() == EntityType::Variable; },
			[](const std::string& str) { return str == "_" || (str.size() > 2 && str[0] == '"' && str[str.size()-1] == '"'); }
	}, lhs);
}

// Allowed RHS expressions:
// - Wildcard _
// - Expression for exact match(e.g. "x*y")
// - Expression for partial match(e.g._"x*y"_)
bool AssignPatternPredicate::isValidRhs(const std::string& rhs) {
	size_t len = rhs.size();
	return rhs == "_" ||
		len > 2 && rhs[0] == '"' && rhs[len - 1] == '"' ||
		len > 4 && rhs[0] == '_' && rhs[1] == '"' && rhs[len - 2] == '"' && rhs[len - 1] == '_';
	}

std::shared_ptr<Strategy> AssignPatternPredicate::getStrategy() const {
	// Implementation logic for returning the appropriate strategy
	return nullptr; // Placeholder return
}