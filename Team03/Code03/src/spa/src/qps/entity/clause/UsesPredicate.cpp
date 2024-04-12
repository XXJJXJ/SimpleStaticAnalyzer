// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "UsesPredicate.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/HeaderTable.h"

UsesPredicate::UsesPredicate(ProcAndStmtRef lhs, EntityRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidProcAndStmtRef(this->lhs) || !isValidVariable(this->rhs)) {
        throw SemanticErrorException("Invalid arguments for UsesPredicate constructor");
    }
    addProcAndStmtRef(this->lhs);
    addEntityRef(this->rhs);
}

// ai-gen end

std::shared_ptr<BaseTable> UsesPredicate::getFullTable(QueryManager &qm) {
    // Gets full table for both procedure and statement, then concatenate them
    auto procTable = std::make_shared<BaseTable>(qm.getUseByProcedure(), 2);
    auto stmtTable = std::make_shared<BaseTable>(qm.getUseByType(EntityType::Stmt), 2);
    procTable->append(*stmtTable);
    return procTable;
}

PredicateType UsesPredicate::getType() const {
    return PredicateType::Uses;
}

bool UsesPredicate::operator==(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const UsesPredicate&>(other);
    return this->lhs == castedOther.lhs && this->rhs == castedOther.rhs;
}
size_t UsesPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (std::hash<ProcAndStmtRef>()(lhs) << 1) 
            ^ (std::hash<EntityRef>()(rhs) >> 1);
}
