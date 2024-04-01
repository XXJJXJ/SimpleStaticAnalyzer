#include "JoinWithPredicateStrategy.h"

// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/7c590366-8e0e-40e2-863f-2862fa1ae192

JoinWithPredicateStrategy::JoinWithPredicateStrategy(std::shared_ptr<Predicate> pred)
        : predicate(std::move(pred)) {}

void JoinWithPredicateStrategy::execute(QueryEvaluationContext& context) {

    if (context.isCurrentResultEmpty()) {
        // short-circuit if the result is already empty
        return;
    }

    auto synonyms = predicate->getSynonyms();

    if (synonyms.empty()) {
        // No synonym involved in the predicate, returns boolean table
        auto table = predicate->getResultTable(context);
        if (table->isEmpty()) {
            context.setResultToFalse();
        }
        return;
    }

    // Check if the table is initialized for the synonyms
    // Check one synonym is enough as all synonyms in the group share the same table
    bool isTableInitialized = context.isTableInitialized(*synonyms[0]);

    if (!isTableInitialized) {
        // If no table is initialized, fetch the table for the predicate and initialize for the group
        auto targetTable =
                std::dynamic_pointer_cast<HeaderTable>(predicate->getResultTable(context));
        if (targetTable) {
            if (targetTable->isEmpty()) {
                context.setResultToFalse();
                return;
            }
            // Initialize the table for the first synonym, which implicitly covers the whole group
            context.putTableForSynonymGroup(*synonyms[0], targetTable);
        }
    } else {
        // If the table is already initialized, update the table for the corresponding group
        for (const auto& synonym : synonyms) {
            auto currentTable = context.getTableForSynonym(*synonym);
            auto targetTable =
                    std::dynamic_pointer_cast<HeaderTable>(predicate->getResultTable(context));
            if (currentTable && targetTable) {
                auto updatedTable =
                        std::dynamic_pointer_cast<HeaderTable>(currentTable->join(*targetTable));
                if (updatedTable->isEmpty()) {
                    context.setResultToFalse();
                }
                // Update the table for the entire synonym group
                context.putTableForSynonymGroup(*synonym, updatedTable);
                break; // Once updated, no need to process further synonyms in the group
            }
        }
    }
}

// ai-gen end