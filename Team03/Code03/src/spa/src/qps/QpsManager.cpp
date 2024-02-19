/*
* Created by ZHENGTAO JIANG on 8/2/24.
*/

#include "QpsManager.h"
#include "QueryEvaluator.h"
#include "QueryParser.h"
#include "QueryValidator.h"
#include "QueryTokenizer.h"
#include <fstream>
#include <iostream>

QpsManager::QpsManager() {}
QpsManager::~QpsManager() {}

std::vector<std::string> QpsManager::processQuery(std::string query) {
    std::vector<std::vector<std::vector<std::string>>> tokens = tokenizeQuery(query);
    std::shared_ptr<Query> parsedQuery = parseQuery(tokens);
    std::vector<std::string> results = evaluateQuery(parsedQuery);
    
    return results;
}

std::vector<std::vector<std::vector<std::string>>> QpsManager::tokenizeQuery(const std::string& query) {
    QueryTokenizer tokenizer;
    return tokenizer.tokenize(query);
}

std::shared_ptr<Query> QpsManager::parseQuery(std::vector<std::vector<std::vector<std::string>>> tokens) {
    QueryParser parser;
    return parser.parse(tokens);
}

vector<std::string> QpsManager::evaluateQuery(const std::shared_ptr<Query> parsedQuery) {
    QueryEvaluator evaluator = QueryEvaluator();
    return evaluator.evaluate(parsedQuery);
}