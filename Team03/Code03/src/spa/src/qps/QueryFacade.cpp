/*
* Created by ZHENGTAO JIANG on 8/2/24.w
*/

#include "QueryFacade.h"
#include "QueryEvaluator.h"
#include "QueryParser.h"
#include "QueryValidator.h"
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
            std::string parsedQuery = parseQuery(query);

            if (validateQuery(parsedQuery)) {
                std::string result = evaluateQuery(parsedQuery);
                results.push_back(result);
            } else {
                results.push_back("Invalid query");
            }
        }

        input.close();

        writeResults(results, outputFile);
    } else {
        std::cerr << "Error: Unable to open input file." << std::endl;
    }
}

std::string QueryFacade::parseQuery(const std::string& query) {
    QueryParser parser;
    return parser.parse(query);
}

bool QueryFacade::validateQuery(const std::string& parsedQuery) {
    QueryValidator validator;
    return validator.validate(parsedQuery);
}

std::string QueryFacade::evaluateQuery(const std::string& validatedQuery) {
    shared_ptr<Query> query;
    QueryEvaluator evaluator = QueryEvaluator();
    return evaluator.evaluate(query);
}

void QueryFacade::writeResults(const std::vector<std::string>& results, const std::string& outputFile) {
    std::ofstream output(outputFile);

    if (output.is_open()) {

        for (const auto& result : results) {
            output <<  result << std::endl;
        }

        output.close();

        std::cout << "Results written to: " << outputFile << std::endl;
    } else {
        std::cerr << "Error: Unable to open output file." << std::endl;
    }
}