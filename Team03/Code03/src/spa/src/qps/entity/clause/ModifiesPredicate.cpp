// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "ModifiesPredicate.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/evaluation/HeaderTable.h"

ModifiesPredicate::ModifiesPredicate(ProcAndStmtRef lhs, EntityRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidProcAndStmtRef(this->lhs) || !isValidVariable(this->rhs)) {
        throw SemanticErrorException("Invalid arguments for ModifiesPredicate constructor");
    }
    addProcAndStmtRef(this->lhs);
    addEntityRef(this->rhs);
}

std::shared_ptr<BaseTable> ModifiesPredicate::getFullTable(QueryManager& qm) {
    auto procTable = std::make_shared<BaseTable>(qm.getModifyByProcedure(), 2);
    auto stmtTable = std::make_shared<BaseTable>(qm.getModifyByType(EntityType::Stmt), 2);
    procTable->append(*stmtTable);
    return procTable;
}

PredicateType ModifiesPredicate::getType() const {
    return PredicateType::Modifies;
}
// ai-gen end
bool ModifiesPredicate::operator==(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const ModifiesPredicate&>(other);
    return this->lhs == castedOther.lhs && this->rhs == castedOther.rhs;
}
size_t ModifiesPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (std::hash<ProcAndStmtRef>()(lhs) << 1) 
            ^ (std::hash<EntityRef>()(rhs) >> 1);
}