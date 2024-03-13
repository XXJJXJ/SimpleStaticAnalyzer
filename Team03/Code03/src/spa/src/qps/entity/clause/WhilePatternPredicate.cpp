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

std::string WhilePatternPredicate::toString() const {
    return "While Pattern Predicate";
}