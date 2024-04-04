#include "PredicateFactory.h"
#include "qps/QueryValidator.h"
#include "qps/entity/clause/AffectsPredicate.h"
#include "qps/entity/clause/AssignPatternPredicate.h"
#include "qps/entity/clause/FollowsPredicate.h"
#include "qps/entity/clause/FollowsTPredicate.h"
#include "qps/entity/clause/ModifiesPredicate.h"
#include "qps/entity/clause/ParentPredicate.h"
#include "qps/entity/clause/ParentTPredicate.h"
#include "qps/entity/clause/UsesPredicate.h"
#include "qps/entity/clause/CallsPredicate.h"
#include "qps/entity/clause/CallsTPredicate.h"
#include "qps/entity/clause/NextPredicate.h"
#include "qps/entity/clause/NextTPredicate.h"
#include "qps/entity/clause/IfPatternPredicate.h"
#include "qps/entity/clause/WhilePatternPredicate.h"
#include "qps/entity/clause/WithPredicate.h"
#include "qps/entity/clause/NotPredicate.h"
#include "qps/entity/clause/attribute/ProcNameExtractor.h"
#include "qps/entity/clause/attribute/VarNameExtractor.h"
#include "qps/entity/clause/attribute/ValueExtractor.h"
#include "qps/entity/clause/attribute/StmtNumberExtractor.h"
#include "common/spa_exception/SemanticErrorException.h"

std::shared_ptr<Predicate> PredicateFactory::createPredicate(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap) {	
	PredicateType predicateType = getPredicateType(tokens[0]);

    switch (predicateType) {
    case PredicateType::Follows: {
        FollowsPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToStatementRef(tokens[2], synonymMap));
        return std::make_shared<FollowsPredicate>(predicate);
    } case PredicateType::FollowsT: {
        FollowsTPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToStatementRef(tokens[2], synonymMap));
        return std::make_shared<FollowsTPredicate>(predicate);
    } case PredicateType::Modifies: {
        ModifiesPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToEntityRef(tokens[2], synonymMap));
        return std::make_shared<ModifiesPredicate>(predicate);
    } case PredicateType::Parent: {
        ParentPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToStatementRef(tokens[2], synonymMap));
        return std::make_shared<ParentPredicate>(predicate);
    } case PredicateType::ParentT: {
        ParentTPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToStatementRef(tokens[2], synonymMap));
        return std::make_shared<ParentTPredicate>(predicate);
    } case PredicateType::Uses: {
        UsesPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToEntityRef(tokens[2], synonymMap));
        return std::make_shared<UsesPredicate>(predicate);
    } case PredicateType::Calls: {
        CallsPredicate predicate(stringToEntityRef(tokens[1], synonymMap), stringToEntityRef(tokens[2], synonymMap));
        return std::make_shared<CallsPredicate>(predicate);
    } case PredicateType::CallsT: {
        CallsTPredicate predicate(stringToEntityRef(tokens[1], synonymMap), stringToEntityRef(tokens[2], synonymMap));
        return std::make_shared<CallsTPredicate>(predicate);
    } case PredicateType::Next: {
        NextPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToStatementRef(tokens[2], synonymMap));
        return std::make_shared<NextPredicate>(predicate);
    } case PredicateType::NextT: {
        NextTPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToStatementRef(tokens[2], synonymMap));
        return std::make_shared<NextTPredicate>(predicate);
    } case PredicateType::Affects: {
        AffectsPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToStatementRef(tokens[2], synonymMap));
        return std::make_shared<AffectsPredicate>(predicate);
    } case PredicateType::Pattern: {
        return parsePatternPredicate(tokens, synonymMap);
    } case PredicateType::With: {
        return parseWithPredicate(tokens, synonymMap);
    } case PredicateType::Not: {
        return parseNotPredicate(tokens, synonymMap);
    }
    }
}

std::variant<int, Synonym, std::string> PredicateFactory::stringToStatementRef(const std::string& token, const std::unordered_map<std::string, EntityType>& synonymMap) {
	size_t len = token.size();
    if (len >= 2 && token[0] == '"' && token[len - 1] == '"') {
        return token.substr(1, len - 2);
	}
	else if (token == "_") {
		return token;
	}
	else if (QueryValidator::isInteger(token)) {
		return stoi(token);
	}
	else if (QueryValidator::isSynonym(token)) {
		return Synonym(token, synonymMap);
	}
}

std::variant<Synonym, std::string> PredicateFactory::stringToEntityRef(const std::string& token, const std::unordered_map<std::string, EntityType>& synonymMap) {
	size_t len = token.size();
	if (len >= 2 && token[0] == '"' && token[len - 1] == '"') {
		return token.substr(1, len - 2);
	}
	else if (token == "_") {
		return token;
	}
	else if (QueryValidator::isSynonym(token)) {
		return Synonym(token, synonymMap);
	}
}

std::variant<std::string, int, AttrRef> PredicateFactory::stringToRef(const std::string& token, const std::unordered_map<std::string, EntityType>& synonymMap) {
    size_t len = token.size();
	if (len >= 2 && token[0] == '"' && token[len - 1] == '"') {
		return token.substr(1, len - 2);
	}
	else if (QueryValidator::isInteger(token)) {
		return stoi(token);
	}
	else if (QueryValidator::isAttrRef(token)) {
        size_t pos = token.find('.');
        Synonym synonym(token.substr(0, pos), synonymMap);
        EntityType entityType = synonym.getType();
        AttributeType attributeType = getAttributeType(token.substr(pos + 1));
        
        switch (attributeType) {
        case AttributeType::ProcName:
            return AttrRef(std::make_shared<Synonym>(synonym), attributeType, std::make_shared<ProcNameExtractor>());
        case AttributeType::VarName:
            return AttrRef(std::make_shared<Synonym>(synonym), attributeType, std::make_shared<VarNameExtractor>());
        case AttributeType::Value:
            return AttrRef(std::make_shared<Synonym>(synonym), attributeType, std::make_shared<ValueExtractor>());
        case AttributeType::StmtNumber:
            return AttrRef(std::make_shared<Synonym>(synonym), attributeType, std::make_shared<StmtNumberExtractor>());
        }
	}
}

std::shared_ptr<Predicate> PredicateFactory::parsePatternPredicate(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap) {
    Synonym syn = Synonym(tokens[1], synonymMap);
    EntityType entityType = syn.getType();

    switch (entityType) {
    case EntityType::Assign: {
        if (tokens.size() != 4) {
            throw SemanticErrorException("Invalid Assign pattern arguments");
        }
        AssignPatternPredicate predicate(syn, stringToEntityRef(tokens[2], synonymMap), tokens[3]);
        return std::make_shared<AssignPatternPredicate>(predicate);
    }
    case EntityType::While: {
        if (tokens.size() != 4 || tokens[3] != "_") {
            throw SemanticErrorException("Invalid While pattern arguments");
        }
        WhilePatternPredicate predicate(syn, stringToEntityRef(tokens[2], synonymMap));
        return std::make_shared<WhilePatternPredicate>(predicate);
    }
    case EntityType::If: {
        if (tokens.size() != 5) {
            throw SemanticErrorException("Invalid If pattern arguments");
        }
        IfPatternPredicate predicate(syn, stringToEntityRef(tokens[2], synonymMap));
        return std::make_shared<IfPatternPredicate>(predicate);
    }
    default: {
        throw SemanticErrorException("Invalid synonym type for pattern predicate");
    }
    }
}

std::shared_ptr<Predicate> PredicateFactory::parseWithPredicate(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap) {
    WithPredicate withPredicate(stringToRef(tokens[1], synonymMap), stringToRef(tokens[2], synonymMap));
    return std::make_shared<WithPredicate>(withPredicate);
}

std::shared_ptr<Predicate> PredicateFactory::parseNotPredicate(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap) {
    std::vector<std::string> predicateTokens(tokens.begin() + 1, tokens.end());
    std::shared_ptr<Predicate> predicate = createPredicate(predicateTokens, synonymMap);
    return std::make_shared<NotPredicate>(predicate);
}