/*
* Created by ZHENGTAO JIANG on 6/2/24.
*/

#include "QueryParser.h"
#include "QueryEvaluator.h"
#include "Query.h"
#include "qps/entity/clause/Clause.h"
#include "qps/entity/query/Synonym.h"
#include "common/EntityType.h"
#include <sstream>

QueryParser::QueryParser() {}
QueryParser::~QueryParser() {}

// Given a string, it will return a vector of strings split by " "
std::vector<std::string> QueryParser::tokenizeString(const std::string& query) {
    // Vector to store tokens
    std::string str(query);
    std::vector<std::string> tokens;

    for (auto i = std::strtok(&str[0], " "); i != NULL; i = std::strtok(NULL, " "))
        tokens.push_back(i);

    return tokens;
}

//Given query string, will create Query object
std::string QueryParser::parse(const std::string& query) {
    //Init variables
    QueryEvaluator qe;
    std::vector<std::shared_ptr<Synonym>> synonyms;
    std::vector<std::shared_ptr<Clause>> clauses = {}; //Empty for Sprint 1

    //Tokenize Strings
    std::vector<std::string> tokens = tokenizeString(query);

    //Convert to Synonyms
    for (const auto& str : tokens) {

    }
    
    //Making a Query object
    Query queryObj(synonyms, clauses);
    //Wrapping in a shared_ptr
    std::shared_ptr<Query> sharedQueryObj = std::make_shared<Query>(queryObj);

    //calling next method which returns a string
    return qe.evaluate(sharedQueryObj);
}
