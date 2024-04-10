#include "PredicateUtils.h"
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

PredicateType AssignPatternPredicate::getType() const {
    return PredicateType::AssignPattern;
}

bool AssignPatternPredicate::operator==(const AssignPatternPredicate &other) const {
    return this->assignSyn == other.assignSyn
        && this->lhs == other.lhs 
        && this->rhs == other.rhs;
}

size_t AssignPatternPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (std::hash<EntityRef>()(lhs) << 1) 
            ^ (std::hash<string>()(rhs) >> 1);
}
bool AssignPatternPredicate::equals(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const AssignPatternPredicate&>(other);
    return *this == castedOther;
}



