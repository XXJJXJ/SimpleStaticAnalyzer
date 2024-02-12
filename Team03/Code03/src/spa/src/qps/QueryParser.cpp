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
#include <algorithm>

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

std::string QueryParser::removeSemiColon(std::string token) {
    token.erase(std::remove(token.begin(), token.end(), ';'), token.end());
    return token;
}

EntityType QueryParser::convertStringToEntityType(std::string curr) {
    // ai-gen start(gpt, 1, e)
    // https://chat.openai.com/share/56b9766f-27cb-4a36-a0ed-188e5b5a598a
    EntityType entityType;
    if (curr == "stmt") {
        entityType = EntityType::Stmt;
    }
    else if (curr == "read") {
        entityType = EntityType::Read;
    }
    else if (curr == "print") {
        entityType = EntityType::Print;
    }
    else if (curr == "call") {
        entityType = EntityType::Call;
    }
    else if (curr == "while") {
        entityType = EntityType::While;
    }
    else if (curr == "if") {
        entityType = EntityType::If;
    }
    else if (curr == "assign") {
        entityType = EntityType::Assign;
    }
    else if (curr == "variable") {
        entityType = EntityType::Variable;
    }
    else if (curr == "constant") {
        entityType = EntityType::Constant;
    }
    else if (curr == "procedure") {
        entityType = EntityType::Procedure;
    }
    else {
        // Handle invalid input or unrecognized enum
    }
    //ai-gen end
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
    for (size_t i = 0; i < tokens.size(); ++i) {
    std:string curr = tokens[i];
        EntityType et = convertStringToEntityType(curr);
        Synonym synObj(et, removeSemiColon(tokens[i + 1]));
        std::shared_ptr<Synonym> sharedSynObj = std::make_shared<Synonym>(synObj);
        synonyms.push_back(sharedSynObj);
    }
    
    //Making a Query object
    Query queryObj(synonyms, clauses);
    //Wrapping in a shared_ptr
    std::shared_ptr<Query> sharedQueryObj = std::make_shared<Query>(queryObj);

    //calling next method which returns a string
    return qe.evaluate(sharedQueryObj);
}
