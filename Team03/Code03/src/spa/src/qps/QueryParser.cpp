/*
* Created by ZHENGTAO JIANG on 6/2/24.
*/

#include "QueryParser.h"
#include "QueryEvaluator.h"
#include "qps/entity/query/Query.h"
#include "qps/entity/clause/Clause.h"
#include "qps/entity/query/Synonym.h"
#include "qps/entity/parser/ClauseFactory.h"
#include "qps/entity/parser/ClauseFactoryManager.h"
#include "common/EntityType.h"
#include "qps/entity/parser/DeclarationsParser.h"
#include "qps/entity/parser/SelectionsParser.h"
#include <sstream>
#include <algorithm>
#include <unordered_map>

QueryParser::QueryParser() {}
QueryParser::~QueryParser() {}

//Given tokens, will create Query object
std::shared_ptr<Query> QueryParser::parse(std::vector<std::vector<std::vector<std::string>>> tokens) {
    std::vector<std::shared_ptr<Synonym>> declarations;
    std::vector<std::shared_ptr<Synonym>> selections;
    std::vector<std::shared_ptr<Clause>> clauses;
    DeclarationsParser dp;
    SelectionsParser sp;

    std::unordered_map<std::string, EntityType> synonymMap;

    std::vector<std::vector<std::string>> declarationsTokens = tokens[0];
    std::vector<std::vector<std::string>> selectionsTokens = tokens[1];
    std::vector<std::vector<std::string>> clausesTokens = tokens[2];

    // Create synonym objects for declarations
    for (size_t i = 0; i < declarationsTokens.size(); i++) {
        std::vector<std::string> tokens = declarationsTokens[i];
        std::vector<std::shared_ptr<Synonym>> currentDeclarations = dp.parse(tokens, synonymMap);
        for (std::shared_ptr<Synonym> synonym : currentDeclarations) {
            declarations.push_back(synonym);
        }
    }

    // Create synonym objects for selections
    for (size_t i = 0; i < selectionsTokens.size(); i++) {
        std::vector<std::string> tokens = selectionsTokens[i];
        std::vector<std::shared_ptr<Synonym>> currentSelections = sp.parse(tokens, synonymMap);
        for (std::shared_ptr<Synonym> synonym : currentSelections) {
            selections.push_back(synonym);
        }
    }
    
    // Create clause objects for clauses
    for (size_t i = 0; i < clausesTokens.size(); i++) {
        std::vector<std::string> tokens = clausesTokens[i];
        std::string firstWord = tokens.front();
        ClauseFactory* factory = ClauseFactoryManager::getClauseFactory(firstWord);
        if (factory) {
            std::shared_ptr<Clause> clauseObject = factory->createClauseObject(tokens);
            clauses.push_back(clauseObject);
        }
    }

    Query query(declarations, selections, clauses);
    std::shared_ptr<Query> sharedQueryObj = std::make_shared<Query>(query);

    return sharedQueryObj;
}