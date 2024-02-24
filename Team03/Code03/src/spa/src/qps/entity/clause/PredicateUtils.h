#pragma once

#include <string>
#include <variant>
#include <unordered_set>
#include "common/EntityType.h"
#include "qps/entity/query/Synonym.h"
#include "common/Util.h"

// We cannot do subtype check without initializing the Entity and call .isOfType(), let's get back to something simple.
const unordered_set<EntityType> VALID_STATEMENT_TYPES = {EntityType::Stmt, EntityType::Assign, EntityType::Call,
                                                         EntityType::While, EntityType::If, EntityType::Read,
                                                         EntityType::Print};

const unordered_set<EntityType> VALID_PROCEDURE_TYPES = {EntityType::Procedure};

// design-entity : 'stmt' | 'read' | 'print' | 'call' | 'while' |
//                'if' | 'assign' | 'variable' | 'constant' | 'procedure'
const unordered_set<EntityType> VALID_DESIGN_ENTITY_TYPES = {EntityType::Stmt, EntityType::Read, EntityType::Print,
                                                             EntityType::Call, EntityType::While, EntityType::If,
                                                             EntityType::Assign, EntityType::Variable,
                                                             EntityType::Constant,
                                                             EntityType::Procedure};
const string WILDCARD = "_";

template<class... Ts>
struct overloaded : Ts ... {
    using Ts::operator()...;
};
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;


using StatementRef = std::variant<int, Synonym, std::string>; // stmtRef: synonym | '_' | INTEGER
using EntityRef = std::variant<Synonym, std::string>; // entRef : synonym | '_' | '"' IDENT '"'


bool isValidStatementRef(const StatementRef &ref);
bool isValidEntityRef(const EntityRef &ref);
bool isWildcard(StatementRef& ref);
bool isWildcard(EntityRef & ref);