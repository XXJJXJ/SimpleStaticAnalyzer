
#include "QueryFacade.h"
#include "QueryEvaluator.h"
#include "QueryParser.h"
#include "QueryValidator.h"
#include "QueryTokenizer.h"
#include "qps/entity/evaluation/EvaluationPlanner.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/spa_exception/SemanticErrorException.h"
#include <iostream>

QueryFacade::QueryFacade() {}
QueryFacade::~QueryFacade() {}

std::vector<std::string> QueryFacade::processQuery(std::string query) {
    try {
        std::vector<std::vector<std::vector<std::string>>> tokens = tokenizeQuery(query);
        std::shared_ptr<Query> parsedQuery = parseQuery(tokens);
        std::vector<std::string> results = evaluateQuery(parsedQuery);
        return results;
    }
    catch (SyntaxErrorException s) {
        return { "SyntaxError" };
    }
    catch (SemanticErrorException s) {
        return { "SemanticError" };
    } 
}

std::vector<std::vector<std::vector<std::string>>> QueryFacade::tokenizeQuery(const std::string& query) {
    QueryTokenizer tokenizer;
    return tokenizer.tokenize(query);
}

std::shared_ptr<Query> QueryFacade::parseQuery(std::vector<std::vector<std::vector<std::string>>> tokens) {
    QueryParser parser;
    return parser.parse(tokens);
}

vector<std::string> QueryFacade::evaluateQuery(const std::shared_ptr<Query> parsedQuery) {
    auto evaluator = make_shared<QueryEvaluator>();
    auto planner = EvaluationPlanner(parsedQuery, evaluator);
    planner.plan();
    return evaluator->evaluate(parsedQuery);
}