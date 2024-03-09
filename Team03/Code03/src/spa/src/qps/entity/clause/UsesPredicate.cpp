// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "UsesPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"
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

std::shared_ptr<BaseTable> UsesPredicate::getFullTable(QueryManager &qm) {
    if (std::holds_alternative<Synonym>(this->lhs)) {
        Synonym synonym = std::get<Synonym>(this->lhs);
        return std::make_shared<BaseTable>(qm.getUseByType(synonym.getType()), 2);
    } else if (std::holds_alternative<int>(this->lhs)) {
        return std::make_shared<BaseTable>(qm.getUseByType(EntityType::Stmt), 2);
    } else {
        return std::make_shared<BaseTable>(qm.getUseByProcedure(), 2);
    }
}


// ai-gen end