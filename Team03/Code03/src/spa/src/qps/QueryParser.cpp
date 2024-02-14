/*
* Created by ZHENGTAO JIANG on 6/2/24.
*/

#include "QueryParser.h"
#include "QueryEvaluator.h"
#include "qps/entity/query/Query.h"
#include "qps/entity/clause/Clause.h"
#include "qps/entity/query/Synonym.h"
#include "common/EntityType.h"
#include <sstream>
#include <algorithm>

QueryParser::QueryParser() {}
QueryParser::~QueryParser() {}


std::pair<std::vector<std::vector<std::string>>, std::vector<std::string>> QueryParser::tokenizeString(const std::string& query) {
    std::istringstream iss(query);

    std::pair<std::vector<std::vector<std::string>>, std::vector<std::string>> tokens;
    std::vector<std::string> currentDeclarations;
    std::vector<std::vector<std::string>> declarations;
    std::vector<std::string> selections;
    std::string token;
    bool isDeclaration = true;

    while (iss >> token) {
        if (isDeclaration) {
            if (token == "Select") {
                tokens.first = declarations;
                isDeclaration = false;
            }
            else {
                if (token.back() == ';') {
                    token.pop_back();
                    currentDeclarations.push_back(token);
                    declarations.push_back(currentDeclarations);
                    currentDeclarations.clear();
                }
                else {
                    currentDeclarations.push_back(token);
                }
            }
        }
        else {
            selections.push_back(token);
        }
    }

    tokens.second = selections;

    return tokens;
}


EntityType QueryParser::convertStringToEntityType(std::string curr) {
    // ai-gen start(gpt, 1, e)
    // https://chat.openai.com/share/56b9766f-27cb-4a36-a0ed-188e5b5a598a

    EntityType entityType{};

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
        //None of the above, gives a Unknown Entity type
        entityType = EntityType::Unknown;
    }
    //ai-gen end

    return entityType;
}

//Given query string, will create Query object
std::shared_ptr<Query> QueryParser::parse(const std::string& query) {
    //Init variables
    QueryEvaluator qe;
    std::vector<std::shared_ptr<Synonym>> synonyms;
    std::vector<std::shared_ptr<Clause>> clauses = {}; //Empty for Sprint 1
    std::shared_ptr<Synonym> selectedSynonyms;
    std::shared_ptr<Synonym> sharedSelectedSynObj;

    std::pair<std::vector<std::vector<std::string>>, std::vector<std::string>> tokens = tokenizeString(query);

    //Convert to Synonyms
    std::vector<std::vector<std::string>> declarations = tokens.first;
    for (size_t i = 0; i < declarations.size(); i++) {
        std::vector<std::string> declaration = declarations[i];
        EntityType entityType = convertStringToEntityType(declaration[0]);
        Synonym synonym(entityType, declaration[1]);
        std::shared_ptr<Synonym> sharedSynonym = std::make_shared<Synonym>(synonym);
        synonyms.push_back(sharedSynonym);
    }

    //Convert to Selected Synonyms
    std::vector<std::string> selections = tokens.second;
    std::string token = selections[0];
    for (const auto& synonym : synonyms) {
        if (synonym->getName() == token) {
            EntityType entityType = synonym->getType();
            Synonym selectedSynonym(entityType, token);
            sharedSelectedSynObj = std::make_shared<Synonym>(selectedSynonym);
        }
    }

    //Making a Query object
    Query queryObj(synonyms, sharedSelectedSynObj, clauses);
    //Wrapping in a shared_ptr
    std::shared_ptr<Query> sharedQueryObj = std::make_shared<Query>(queryObj);

    return sharedQueryObj;
}
