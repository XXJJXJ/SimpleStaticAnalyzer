#include "QpsManager.h"

QpsManager::QpsManager() {}

QpsManager::~QpsManager() {}

std::vector<std::string> QpsManager::processQuery(std::string query) {
    try {
        std::vector<std::vector<std::vector<std::string>>> tokens = tokenizeQuery(query);
        std::shared_ptr<Query> parsedQuery = parseQuery(tokens);
        std::vector<std::string> results = evaluateQuery(parsedQuery);
    }
    catch (SyntaxErrorException s) {
        return {"SyntaxError"};
    }
    catch (SemanticErrorException s) {
        return {"SemanticError"};
    }
}

// Calls QueryTokenizer to tokenize the query string
std::vector<std::vector<std::vector<std::string>>>
QpsManager::tokenizeQuery(const std::string &query) {
    QueryTokenizer tokenizer;
    return tokenizer.tokenize(query);
}

// Calls QueryParser to parse the tokens into a Query object
std::shared_ptr<Query>
QpsManager::parseQuery(std::vector<std::vector<std::vector<std::string>>> tokens) {
    QueryParser parser;
    return parser.parse(tokens);
}

vector<std::string> QpsManager::evaluateQuery(const std::shared_ptr<Query> parsedQuery) {
    auto evaluator = make_shared<QueryEvaluator>();
    auto planner = EvaluationPlanner(parsedQuery, evaluator);
    planner.plan();
    return evaluator->evaluate(parsedQuery);
}