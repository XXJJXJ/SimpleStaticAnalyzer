#include "QpsManager.h"

QpsManager::QpsManager() = default;

QpsManager::~QpsManager() = default;

std::vector<std::string> QpsManager::processQuery(const std::string &query) {
    try {
        std::vector<std::string> tokens = tokenizeQuery(query);
        std::vector<std::vector<std::vector<std::string>>> validatedTokens = validateQuery(tokens);
        std::shared_ptr<Query> parsedQuery = parseQuery(validatedTokens);
        std::vector<std::string> results = evaluateQuery(parsedQuery);
        return results;
    } catch (SyntaxErrorException syntaxError) {
        return {"SyntaxError"};
    } catch (SemanticErrorException semanticError) {
        return {"SemanticError"};
    }
}

// Calls QueryTokenizer to tokenize the query string
std::vector<std::string> QpsManager::tokenizeQuery(const std::string &query) {
    return QueryTokenizer::tokenize(query);
}

std::vector<std::vector<std::vector<std::string>>> QpsManager::validateQuery(std::vector<std::string> tokens) {
    return QueryValidator::validate(tokens);
}

// Calls QueryParser to parse the tokens into a Query object
std::shared_ptr<Query> QpsManager::parseQuery(std::vector<std::vector<std::vector<std::string>>> tokens) {
    QueryParser parser;
    return parser.parse(tokens);
}

vector<std::string> QpsManager::evaluateQuery(const std::shared_ptr<Query> parsedQuery) {
    auto evaluator = make_shared<QueryEvaluator>();
    auto planner = EvaluationPlanner(parsedQuery, evaluator);
    planner.plan();
    return evaluator->evaluate(parsedQuery);
}