#include "PredicateUtils.h"

PredicateType getPredicateType(const std::string &keyword) {
    static const std::unordered_map<std::string, PredicateType> keywordMap =
        {{"Follows", PredicateType::Follows}, {"Follows*", PredicateType::FollowsT},
         {"Modifies", PredicateType::Modifies}, {"Parent", PredicateType::Parent}, {"Parent*", PredicateType::ParentT},
         {"Uses", PredicateType::Uses}, {"pattern", PredicateType::Pattern}, {"assign", PredicateType::AssignPattern},
         {"if", PredicateType::IfPattern}, {"while", PredicateType::WhilePattern}, {"Calls", PredicateType::Calls},
         {"Calls*", PredicateType::CallsT}, {"Next", PredicateType::Next}, {"Next*", PredicateType::NextT},
         {"Affects", PredicateType::Affects}, {"with", PredicateType::With}, {"not", PredicateType::Not}};

    auto it = keywordMap.find(keyword);
    return (it != keywordMap.end()) ? it->second : PredicateType::Invalid;
}

AttributeType getAttributeTypeFromString(const std::string &attribute) {
    static const std::unordered_map<std::string, AttributeType> attributeMap =
        {{"procName", AttributeType::ProcName}, {"varName", AttributeType::VarName}, {"value", AttributeType::Value},
         {"stmt#", AttributeType::StmtNumber}};
    auto it = attributeMap.find(attribute);
    return (it != attributeMap.end()) ? it->second : AttributeType::Invalid;
}

// Semantic check for whether synonym is a statement, or if statement number > 0
bool isValidStatementRef(const StatementRef &ref) {
    if (std::holds_alternative<Synonym>(ref)) {
        auto synonym = std::get<Synonym>(ref);
        return VALID_STATEMENT_TYPES.find(synonym.getType()) != VALID_STATEMENT_TYPES.end();
    } else if (std::holds_alternative<int>(ref)) {
        // Assuming int is always a valid statement reference
        return std::get<int>(ref) > 0;
    }
    return true;
}

// Semantic check for whether synonym is an entity
bool isValidEntityRef(const EntityRef &ref) {
    if (std::holds_alternative<Synonym>(ref)) {
        auto synonym = std::get<Synonym>(ref);
        return VALID_DESIGN_ENTITY_TYPES.find(synonym.getType()) != VALID_DESIGN_ENTITY_TYPES.end();
    }
    return true;
}

// Semantic check for whether synonym is a statement or an entity, or if statement number > 0
bool isValidProcAndStmtRef(const ProcAndStmtRef &ref) {
    if (std::holds_alternative<Synonym>(ref)) {
        auto synonym = std::get<Synonym>(ref);
        return VALID_STATEMENT_TYPES.find(synonym.getType()) != VALID_STATEMENT_TYPES.end()
            || VALID_PROCEDURE_TYPES.find(synonym.getType()) != VALID_PROCEDURE_TYPES.end();
    } else if (std::holds_alternative<std::string>(ref)) {
        std::string refString = std::get<std::string>(ref);
        return refString != WILDCARD;
    } else if (std::holds_alternative<int>(ref)) {
        // Assuming int is always a valid statement reference
        return std::get<int>(ref) > 0;
    }
    return true;
}

// Semantic check for whether synonym is a variable
bool isValidVariable(const EntityRef &ref) {
    if (std::holds_alternative<Synonym>(ref)) {
        auto synonym = std::get<Synonym>(ref);
        return synonym.getType() == EntityType::Variable;
    }
    return true;
}

// Semantic check for whether synonym is a procedure
bool isValidProcedure(const EntityRef &ref) {
    if (std::holds_alternative<Synonym>(ref)) {
        auto synonym = std::get<Synonym>(ref);
        return synonym.getType() == EntityType::Procedure;
    }
    return true;
}

bool isValidEntityRefWithType(const EntityRef &ref, EntityType type) {
    if (!isValidEntityRef(ref)) {
        return false;
    }
    if (std::holds_alternative<Synonym>(ref)) {
        auto synonym = std::get<Synonym>(ref);
        return synonym.getType() == type;
    }
    return true;
}

bool isWildcard(StatementRef &ref) {
    return std::holds_alternative<std::string>(ref) && std::get<std::string>(ref) != WILDCARD;
}

bool isWildcard(EntityRef &ref) {
    return std::holds_alternative<std::string>(ref) && std::get<std::string>(ref) != WILDCARD;
}

bool hasWildcard(std::string &expr) {
    // if both first and last are "_", then it's a wildcard
    return (expr.size() > 1 && expr[0] == '_' && expr[expr.size() - 1] == '_') || expr == "_";
}

std::string stripWildcard(std::string &expr) {
    if (expr == "_") {
        return "";
    }
    if (hasWildcard(expr)) {
        // Remove _" and "_
        return expr.substr(2, expr.size() - 4);
    } else {
        // Remove " and "
        return expr.substr(1, expr.size() - 2);
    }

}


