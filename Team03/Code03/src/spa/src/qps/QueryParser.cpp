/*
 * Created by ZHENGTAO JIANG on 6/2/24.
 */

#include <algorithm>
#include <sstream>

#include "QueryParser.h"
#include "QueryEvaluator.h"

<<<<<<< HEAD

#include "qps/entity/query/Query.h"
#include "qps/entity/query/Synonym.h"
#include "qps/entity/parser/PredicateFactory.h"
#include "common/EntityType.h"
=======

#include "common/EntityType.h"
#include "qps/entity/clause/Clause.h"
#include "qps/entity/parser/ClauseFactory.h"
#include "qps/entity/parser/ClauseFactoryManager.h"

>>>>>>> qps-feature-enhance-

components

#include "qps/entity/parser/DeclarationsParser.h"
#include "qps/entity/parser/SelectionsParser.h"
#include "qps/entity/query/Query.h"
#include "qps/entity/query/Synonym.h"
#include <sstream>
#include <algorithm>
#include <unordered_map>

QueryParser::QueryParser() = default;

QueryParser::~QueryParser() = default;

// Given tokens, will create Query object
std::shared_ptr<Query>
QueryParser::parse(std::vector<std::vector<std::vector<std::string>>> tokens) {
    std::vector<std::shared_ptr<Synonym>> declarations;
    std::vector<std::shared_ptr<Synonym>> selections;
    std::vector<std::shared_ptr<Predicate>> predicates;
    SelectionsParser sp;
    PredicateFactory pf;

    std::unordered_map<std::string, EntityType> synonymMap;

    std::vector<std::vector<std::string>> declarationsTokens = tokens[0];
    std::vector<std::vector<std::string>> selectionsTokens = tokens[1];
    std::vector<std::vector<std::string>> predicateTokens = tokens[2];

    // Create synonym objects for declarations
    for (const auto &declareTokens: declarationsTokens) {
        std::vector<std::shared_ptr<Synonym>> currentDeclarations = DeclarationsParser::parse(declareTokens,
                                                                                              synonymMap);
        for (const std::shared_ptr<Synonym> &synonym: currentDeclarations) {
            declarations.push_back(synonym);
        }
    }

    // Create synonym objects for selections
    for (const auto &selectTokens: selectionsTokens) {
        std::vector<std::shared_ptr<Synonym>> currentSelections = sp.parse(selectTokens, synonymMap);
        for (std::shared_ptr<Synonym> synonym: currentSelections) {
            selections.push_back(synonym);
        }
    }
    // Create predicate objects for clauses
    for (auto tokens: predicateTokens) {
        if (tokens.size() > 2 && tokens[0] == "such" && tokens[1] == "that") {
            std::vector<std::string> predicateTokens(tokens.begin() + 2, tokens.end());
            std::shared_ptr<Predicate> predicate = pf.createPredicate(predicateTokens, synonymMap);
            predicates.push_back(predicate);
        } else if (tokens.size() > 1 && tokens[0] == "pattern") {
            std::shared_ptr<Predicate> predicate = pf.createPredicate(tokens, synonymMap);
            predicates.push_back(predicate);
        } else {
            throw SyntaxErrorException("Invalid clause keyword");
        }
    }

    //Query query(declarations, selections, clauses);
    Query query(declarations, selections, predicates);
    std::shared_ptr<Query> sharedQueryObj = std::make_shared<Query>(query);

    return sharedQueryObj;
}