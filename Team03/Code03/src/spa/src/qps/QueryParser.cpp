/*
* Created by ZHENGTAO JIANG on 6/2/24.
* 
* 
*/

#include "QueryParser.h"
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

//Main parsing method
std::string QueryParser::parse(const std::string& query) {
    
    std::vector<std::string> tokens = tokenizeString(query);
    


    return query;
}
