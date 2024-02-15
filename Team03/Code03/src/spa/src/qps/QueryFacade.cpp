/*
* Created by ZHENGTAO JIANG on 8/2/24.
*/

#include "QueryFacade.h"
#include "QueryEvaluator.h"
#include "QueryParser.h"
#include "QueryValidator.h"
#include "QueryTokenizer.h"
#include <fstream>
#include <iostream>

QueryFacade::QueryFacade() {}
QueryFacade::~QueryFacade() {}

void QueryFacade::processQueries(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream input(inputFile);
    std::vector<std::string> results;

    if (input.is_open()) {
        std::string query;
        while (std::getline(input, query)) {
            std::vector<std::vector<std::string>> tokens = tokenizeQuery(query);
            std::shared_ptr<Query> parsedQuery = parseQuery(tokens);
            std::vector<std::string> result = evaluateQuery(parsedQuery);

            std::ofstream output(outputFile, std::ofstream::app);

            if (output.is_open()) {
                for (const auto& res : result) {
                    output << res << std::endl;
                }
                output.close();
            }
            else {
                std::cerr << "Error: Unable to open output file." << std::endl;
            }

        }

        input.close();

    } else {
        std::cerr << "Error: Unable to open input file." << std::endl;
    }
}

std::vector<std::vector<std::string>> QueryFacade::tokenizeQuery(const std::string& query) {
    QueryTokenizer tokenizer;
    return tokenizer.tokenize(query);
}

std::shared_ptr<Query> QueryFacade::parseQuery(std::vector<std::vector<std::string>> tokens) {
    QueryParser parser;
    return parser.parse(tokens);
}

vector<std::string> QueryFacade::evaluateQuery(const std::shared_ptr<Query> parsedQuery) {
    QueryEvaluator evaluator = QueryEvaluator();
    return evaluator.evaluate(parsedQuery);
}