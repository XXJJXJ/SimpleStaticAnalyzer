// ai-gen start(gpt, 1, e)
#include "DeclarationStrategy.h"
#include <memory>
#include <vector>


DeclarationStrategy::DeclarationStrategy(const std::vector<Synonym>& synonyms)
        : synonyms(synonyms) {}

std::vector<std::shared_ptr<Entity>> DeclarationStrategy::getEntitiesByType(EntityType entityType, QueryManager &queryManager) {
    switch (entityType) {
        case EntityType::Procedure:
            return queryManager.getAllProcedures();
        case EntityType::Stmt:
            return queryManager.getAllStatements();
        case EntityType::Assign:
            return queryManager.getAllAssignStatements();
        case EntityType::Print:
            return queryManager.getAllPrintStatements();
        case EntityType::Read:
            return queryManager.getAllReadStatements();
        case EntityType::Call:
            return queryManager.getAllCallStatements();
        case EntityType::If:
            return queryManager.getAllIfStatements();
        case EntityType::While:
            return queryManager.getAllWhileStatements();
        default:
            // Raise exception for unknown entity type
            throw std::invalid_argument("Unknown entity type");
    }
}

/**
 * Execute the declaration strategy. For each synonym, get all entities of the type and add them to the context.
 * @param context the query evaluation context that provides the query manager and stores the synonym values.
 */
void DeclarationStrategy::execute(QueryEvaluationContext &context) {
    shared_ptr<QueryManager> queryManager = context.getQueryManager();
    for (const auto& synonym : synonyms) {
        auto entities = getEntitiesByType(synonym.getType(), *queryManager);
        SynonymValues synonymValues(synonym);
        for (const auto& entity : entities) {
            synonymValues.addValue(entity);
        }
        context.addSynonymValues(synonymValues);
    }
}

// ai-gen end