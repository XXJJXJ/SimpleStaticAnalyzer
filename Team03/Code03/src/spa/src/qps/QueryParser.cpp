/*
* Created by ZHENGTAO JIANG on 6/2/24.
* 
* 
*/

#include "QueryParser.h"

QueryParser::QueryParser() {}
QueryParser::~QueryParser() {}

// Given a string, it will return a vector of strings split by " "
std::vector<std::string> tokenizeString(const std::string& query) {
    std::string delimiter = " ";
std:vector<std::string> tokens;

    size_t start = 0, end;
    while ((end = query.find(delimiter)) != std::string::npos) {
        tokens.push_back(query.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(query.substr(start));

    return tokens;
}

//Main parsing method
std::string QueryParser::parse(const std::string& query) {
    
    std::vector<std::string> tokens = tokenizeString(query);
    
    return query;
}
