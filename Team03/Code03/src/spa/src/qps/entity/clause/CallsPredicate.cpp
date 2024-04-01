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

std::shared_ptr<BaseTable> CallsPredicate::getFullTable(QueryManager& qm) {
    return make_shared<BaseTable>(qm.getCallS(), 2);
}

PredicateType CallsPredicate::getType() const {
    return PredicateType::Calls;
}