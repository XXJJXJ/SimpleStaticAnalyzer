#include "QpsManager.h"

QpsManager::QpsManager() = default;

QpsManager::~QpsManager() = default;

std::vector<std::string> QpsManager::processQuery(const std::string& query) {
    try {
        std::vector<std::vector<std::vector<std::string>>> tokens = tokenizeQuery(query);
        std::shared_ptr<Query> parsedQuery = parseQuery(tokens);
        std::vector<std::string> results = evaluateQuery(parsedQuery);
    }
    catch (SyntaxErrorException syntaxError) {
        return {"SyntaxError"};
    }
    catch (SemanticErrorException semanticError) {
        return {"SemanticError"};
    }

    return {};
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