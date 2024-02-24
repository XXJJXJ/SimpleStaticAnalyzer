/*
 * Created by ZHENGTAO JIANG on 8/2/24.
 */

#include <fstream>
#include <iostream>

#include "QpsManager.h"
#include "QueryEvaluator.h"
#include "QueryParser.h"
#include "QueryTokenizer.h"
#include "QueryValidator.h"

QpsManager::QpsManager() {}
QpsManager::~QpsManager() {}

std::vector<std::string> QpsManager::processQuery(std::string query) {
    std::vector<std::vector<std::vector<std::string>>> tokens = tokenizeQuery(query);
    std::shared_ptr<Query> parsedQuery = parseQuery(tokens);
    std::vector<std::string> results = evaluateQuery(parsedQuery);

    return results;
}

// Calls QueryTokenizer to tokenize the query string
std::vector<std::vector<std::vector<std::string>>>
QpsManager::tokenizeQuery(const std::string& query) {
    QueryTokenizer tokenizer;
    return tokenizer.tokenize(query);
}

// Calls QueryParser to parse the tokens into a Query object
std::shared_ptr<Query>
QpsManager::parseQuery(std::vector<std::vector<std::vector<std::string>>> tokens) {
    QueryParser parser;
    return parser.parse(tokens);
}

// Calls QueryEvaluator to evaluate the parsed query
vector<std::string> QpsManager::evaluateQuery(const std::shared_ptr<Query> parsedQuery) {
    QueryEvaluator evaluator = QueryEvaluator();
    return evaluator.evaluate(parsedQuery);
}