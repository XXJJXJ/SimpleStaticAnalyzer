#include "CallsPredicate.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/HeaderTable.h"

CallsPredicate::CallsPredicate(EntityRef lhs, EntityRef rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidProcedure(this->lhs) || !isValidProcedure(this->rhs)) {
        throw SemanticErrorException("Invalid argument for CallsPredicate constructor");
    }

    addEntityRef(this->lhs);
    addEntityRef(this->rhs);
}

std::shared_ptr<BaseTable> CallsPredicate::getFullTable(QueryManager &qm) {
    return make_shared<BaseTable>(qm.getCallS(), 2);
}

PredicateType CallsPredicate::getType() const {
    return PredicateType::Calls;
}

bool CallsPredicate::operator==(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const CallsPredicate &>(other);
    return this->lhs == castedOther.lhs && this->rhs == castedOther.rhs;
}
size_t CallsPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (std::hash<EntityRef>()(lhs) << 1)
        ^ (std::hash<EntityRef>()(rhs) >> 1);
}