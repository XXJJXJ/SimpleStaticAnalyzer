#include "CallsTPredicate.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/HeaderTable.h"

CallsTPredicate::CallsTPredicate(EntityRef lhs, EntityRef rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidProcedure(this->lhs) || !isValidProcedure(this->rhs)) {
        throw SemanticErrorException("Invalid argument for CallsPredicate constructor");
    }

    addEntityRef(this->lhs);
    addEntityRef(this->rhs);
}

std::shared_ptr<BaseTable> CallsTPredicate::getFullTable(QueryManager& qm) {
    return make_shared<BaseTable>(qm.getCallT(), 2);
}

PredicateType CallsTPredicate::getType() const {
    return PredicateType::CallsT;
}

bool CallsTPredicate::operator==(const CallsTPredicate &other) const {
    return this->lhs == other.lhs && this->rhs == other.rhs;
}

size_t CallsTPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (std::hash<EntityRef>()(lhs) << 1) 
            ^ (std::hash<EntityRef>()(rhs) >> 1);
}
bool CallsTPredicate::equals(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const CallsTPredicate&>(other);
    return *this == castedOther;
}