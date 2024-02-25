#include "JoinWithPredicateStrategy.h"

// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/7c590366-8e0e-40e2-863f-2862fa1ae192

JoinWithPredicateStrategy::JoinWithPredicateStrategy(std::shared_ptr<Predicate> pred)
        : predicate(std::move(pred)) {}

void JoinWithPredicateStrategy::execute(QueryEvaluationContext& context) {
    auto synonyms = predicate->getSynonyms();

    // Check if the table is initialized for the synonyms
    // Check one synonym is enough as all synonyms in the group share the same table
    bool isTableInitialized = context.isTableInitialized(*synonyms[0]);

    if (!isTableInitialized) {
        // If no table is initialized, fetch the table for the predicate and initialize for the group
        auto targetTable = predicate->getTable(*context.getQueryManager());
        if (targetTable) {
            // Initialize the table for the first synonym, which implicitly covers the whole group
            context.putTableForSynonymGroup(*synonyms[0], targetTable);
        }
    } else {
        // If the table is already initialized, update the table for the corresponding group
        for (const auto& synonym : synonyms) {
            auto currentTable = context.getTableForSynonym(*synonym);
            auto targetTable = predicate->getTable(*context.getQueryManager());
            if (currentTable && targetTable) {
                auto updatedTable = currentTable->join(*targetTable);
                // Update the table for the entire synonym group
                context.putTableForSynonymGroup(*synonym, updatedTable);
                break; // Once updated, no need to process further synonyms in the group
            }
        }
    }
}

// ai-gen end