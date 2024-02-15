/*
* Created by ZHENGTAO JIANG on 6/2/24.
*/

#include "QueryParser.h"
#include "QueryEvaluator.h"
#include "qps/entity/query/Query.h"
#include "qps/entity/clause/Clause.h"
#include "qps/entity/query/Synonym.h"
#include "qps/entity/parser/EntityFactory.h"
#include "qps/entity/parser/EntityFactoryManager.h"
#include "common/EntityType.h"
#include <sstream>
#include <algorithm>

QueryParser::QueryParser() {}
QueryParser::~QueryParser() {}

std::shared_ptr<Query> createQuery(const std::vector<std::shared_ptr<EntityObject>>& entityObjects) {
    std::vector<std::shared_ptr<Synonym>> synonyms;
    std::vector<std::shared_ptr<Clause>> clauses;
    std::shared_ptr<Synonym> selectedSynonym = nullptr;

    for (const auto& entityObject : entityObjects) {
        if (auto synonym = std::dynamic_pointer_cast<Synonym>(entityObject)) {
            synonyms.push_back(synonym);
        }
        else if (auto clause = std::dynamic_pointer_cast<Clause>(entityObject)) {
            clauses.push_back(clause);
        }
        // need to add in Selected synonym - create a new SelectedSynonym class?
    }

    Query query(synonyms, selectedSynonym, clauses);
    std::shared_ptr<Query> sharedQueryObj = std::make_shared<Query>(query);

    return sharedQueryObj;
}

//Given query string, will create Query object
std::shared_ptr<Query> QueryParser::parse(std::vector<std::vector<std::string>> tokens) {
    //Init variables
    std::vector<std::shared_ptr<Synonym>> synonyms;
    std::shared_ptr<Synonym> selectedSynonym;
    std::vector<std::shared_ptr<Clause>> clauses = {}; //Empty for Sprint 1

    std::vector<std::shared_ptr<EntityObject>> entityObjects;

    for (size_t i = 0; i < tokens.size(); i++) {
        std::vector<std::string> token = tokens[i];
        std::string firstWord = token.front();
        EntityFactory* factory = EntityFactoryManager::getEntityFactory(firstWord);
        if (factory) {
            std::shared_ptr<EntityObject> entityObject = factory->createEntityObject(token);
            entityObjects.push_back(entityObject);
        }
    }

    std::shared_ptr<Query> query = createQuery(entityObjects);

    return query;
}