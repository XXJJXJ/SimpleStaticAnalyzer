// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "ParentTPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"

ParentTPredicate::ParentTPredicate(StatementRef lhs, StatementRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidStatementRef(this->lhs) || !isValidStatementRef(this->rhs)) {
        throw SemanticErrorException("Invalid arguments for ParentTPredicate constructor");
    }
    addStmtRef(this->lhs);
    addStmtRef(this->rhs);
}

std::string ParentTPredicate::toString() const {
    std::string lhsStr = std::visit(overloaded {
            [](const int val) { return std::to_string(val); },
            [](const Synonym& syn) { return syn.getName(); },
            [](const std::string& str) { return str; },
            [](const auto&) { return std::string("Unsupported Type"); }
    }, lhs);

    std::string rhsStr = std::visit(overloaded {
            [](const int val) { return std::to_string(val); },
            [](const Synonym& syn) { return syn.getName(); },
            [](const std::string& str) { return str; },
            [](const auto&) { return std::string("Unsupported Type"); }
    }, rhs);

    return "ParentTPredicate " + lhsStr + " " + rhsStr;
}

std::shared_ptr<BaseTable> ParentTPredicate::getFullTable(QueryManager &qm) {
    return std::make_shared<BaseTable>(qm.getParentT(), 2);
}
// ai-gen end