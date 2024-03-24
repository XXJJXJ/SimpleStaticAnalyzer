#include "IfPatternPredicate.h"

std::shared_ptr<BaseTable> IfPatternPredicate::getFullTable(QueryManager &qm) {
    return make_shared<BaseTable>(qm.getIfPattern(), 2);
}

IfPatternPredicate::IfPatternPredicate(Synonym ifSyn, EntityRef entRef)
        : ifSyn(std::move(ifSyn)), entRef(std::move(entRef)) {
    bool isValidIfSyn = this->ifSyn.getType() == EntityType::If;
    bool isValidVarRef = isValidEntityRefWithType(this->entRef, EntityType::Variable);
    if (!isValidIfSyn || !isValidVarRef) {
        throw SemanticErrorException("Invalid argument for IfPatternPredicate constructor");
    }
    EntityRef ifSynRef = this->ifSyn;
    addEntityRef(ifSynRef); // ifSyn is an entityRef as well, as it is a synonym
    addEntityRef(this->entRef);
}

