#include "PredicateInputValidator.h"
#include "common/Util.h"

// We cannot do subtype check without initializing the Entity and call .isOfType(), let's get back to something simple
const unordered_set<EntityType> VALID_STATEMENT_TYPES = {EntityType::Stmt, EntityType::Assign, EntityType::Call,
                                                         EntityType::While, EntityType::If, EntityType::Read,
                                                         EntityType::Print};
const unordered_set<EntityType> VALID_PROCEDURE_TYPES = {EntityType::Procedure};

// Checks the validity of input
bool PredicateInputValidator::isValidStatementRef(const StatementRef &ref) {
    if (std::holds_alternative<Synonym>(ref)) {
        auto synonym = std::get<Synonym>(ref);
        return VALID_STATEMENT_TYPES.find(synonym.getType()) != VALID_STATEMENT_TYPES.end();
    } else if (std::holds_alternative<std::string>(ref)) {
        return std::get<std::string>(ref) == "_";
    } else if (std::holds_alternative<int>(ref)) {
        // Assuming int is always a valid statement reference
        return std::get<int>(ref) > 0;
    }
    return false;
}