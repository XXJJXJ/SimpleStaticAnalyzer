// ai-gen start(gpt, 1, e)
// prompt 1: https://chat.openai.com/share/f0da3797-ca97-4fe7-938b-ca4e00bbe8e1
// prompt 2: https://chat.openai.com/share/90842ec5-59d1-44c7-b7cc-52c6bfa1c405
#include "DeclarationStrategy.h"
#include "pkb/QueryPKB.h"
#include <memory>
#include <vector>


DeclarationStrategy::DeclarationStrategy(const std::vector<shared_ptr<Synonym>>& synonyms)
        : synonyms(synonyms) {}

std::vector<std::shared_ptr<Entity>> DeclarationStrategy::getEntitiesByType(EntityType entityType, QueryManager &queryManager) {
    std::vector<std::shared_ptr<Entity>> baseClassEntities;

    switch (entityType) {
        case EntityType::Procedure: {
            auto entities = queryManager.getAllProcedures();
            baseClassEntities.insert(baseClassEntities.end(), entities.begin(), entities.end());
            break;
        }
        case EntityType::Stmt: {
            auto entities = queryManager.getAllStatements();
            baseClassEntities.insert(baseClassEntities.end(), entities.begin(), entities.end());
            break;
        }
        case EntityType::Assign: {
            auto entities = queryManager.getAllAssignStatements();
            baseClassEntities.insert(baseClassEntities.end(), entities.begin(), entities.end());
            break;
        }
        case EntityType::Print: {
            auto entities = queryManager.getAllPrintStatements();
            baseClassEntities.insert(baseClassEntities.end(), entities.begin(), entities.end());
            break;
        }
        case EntityType::Read: {
            auto entities = queryManager.getAllReadStatements();
            baseClassEntities.insert(baseClassEntities.end(), entities.begin(), entities.end());
            break;
        }
        case EntityType::Call: {
            auto entities = queryManager.getAllCallStatements();
            baseClassEntities.insert(baseClassEntities.end(), entities.begin(), entities.end());
            break;
        }
        case EntityType::If: {
            auto entities = queryManager.getAllIfStatements();
            baseClassEntities.insert(baseClassEntities.end(), entities.begin(), entities.end());
            break;
        }
        case EntityType::While: {
            auto entities = queryManager.getAllWhileStatements();
            baseClassEntities.insert(baseClassEntities.end(), entities.begin(), entities.end());
            break;
        }
        case EntityType::Variable: {
            auto entities = queryManager.getAllVariables();
            baseClassEntities.insert(baseClassEntities.end(), entities.begin(), entities.end());
            break;
        }
        default:
            // Raise exception for unknown entity type
            throw std::invalid_argument("Unknown entity type");
    }

    return baseClassEntities;
}


/**
 * Execute the declaration strategy. For each synonym, get all entities of the type and add them to the context.
 * @param context the query evaluation context that provides the query manager and stores the synonym values.
 */
void DeclarationStrategy::execute(QueryEvaluationContext &context) {
    shared_ptr<QueryManager> queryManager = context.getQueryManager();
    for (const auto& synonym : synonyms) {
        auto entities = getEntitiesByType(synonym->getType(), *queryManager);
        SynonymValues synonymValues(synonym);
        for (const auto& entity : entities) {
            synonymValues.addValue(entity);
        }
        context.addSynonymValues(synonymValues);
    }
}

// ai-gen end