#include "WhilePatternPredicate.h"

std::shared_ptr<BaseTable> WhilePatternPredicate::getFullTable(QueryManager &qm) {
    return make_shared<BaseTable>(qm.getWhilePattern(), 2);
}

WhilePatternPredicate::WhilePatternPredicate(Synonym whileSyn, EntityRef entRef)
        : whileSyn(std::move(whileSyn)), entRef(std::move(entRef)) {
    bool isValidWhileSyn = this->whileSyn.getType() == EntityType::While;
    bool isValidVarRef = isValidEntityRefWithType(this->entRef, EntityType::Variable);
    if (!isValidWhileSyn || !isValidVarRef) {
        throw SemanticErrorException("Invalid argument for WhilePatternPredicate constructor");
    }
    EntityRef whileSynRef = this->whileSyn;
    addEntityRef(whileSynRef); // WhileSyn is an entityRef as well, as it is a synonym
    addEntityRef(this->entRef);
}

PredicateType WhilePatternPredicate::getType() const {
    return PredicateType::WhilePattern;
}

bool WhilePatternPredicate::operator==(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const WhilePatternPredicate&>(other);
    return this->whileSyn == castedOther.whileSyn && this->entRef == castedOther.entRef;
}
size_t WhilePatternPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (std::hash<Synonym>()(whileSyn) << 1) 
            ^ (std::hash<EntityRef>()(entRef) >> 1);
}