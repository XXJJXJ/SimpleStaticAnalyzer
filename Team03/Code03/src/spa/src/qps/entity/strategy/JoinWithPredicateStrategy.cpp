#include "JoinWithPredicateStrategy.h"

// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/7c590366-8e0e-40e2-863f-2862fa1ae192

JoinWithPredicateStrategy::JoinWithPredicateStrategy(std::shared_ptr<Predicate> pred)
        : predicate(std::move(pred)) {}

void JoinWithPredicateStrategy::handleNoSynonyms(QueryEvaluationContext& context) {
    auto table = predicate->getResultTable(context);
    if (table->isEmpty()) {
        context.setResultToFalse();
    }
}

void JoinWithPredicateStrategy::initializeTable(QueryEvaluationContext& context, const std::vector<shared_ptr<Synonym>>& synonyms) {
    auto targetTable = std::dynamic_pointer_cast<HeaderTable>(predicate->getResultTable(context));
    if (targetTable && targetTable->isEmpty()) {
        context.setResultToFalse();
        return;
    }
    context.putTableForSynonymGroup(*synonyms[0], targetTable);
}

void JoinWithPredicateStrategy::updateTable(QueryEvaluationContext& context, const std::vector<shared_ptr<Synonym>>& synonyms) {
    for (const auto& synonym : synonyms) {
        auto currentTable = context.getTableForSynonym(*synonym);
        auto targetTable = std::dynamic_pointer_cast<HeaderTable>(predicate->getResultTable(context));
        if (currentTable && targetTable) {
            auto updatedTable = std::dynamic_pointer_cast<HeaderTable>(currentTable->join(*targetTable));
            if (updatedTable->isEmpty()) {
                context.setResultToFalse();
            }
            context.putTableForSynonymGroup(*synonym, updatedTable);
            break; // Once updated, no need to process further synonyms in the group
        }
    }
}

void JoinWithPredicateStrategy::execute(QueryEvaluationContext& context) {
    if (context.isCurrentResultEmpty()) {
        return; // Short-circuit if the result is already empty
    }

    auto synonyms = predicate->getSynonyms();
    if (synonyms.empty()) {
        handleNoSynonyms(context);
        return;
    }

    bool isTableInitialized = context.isTableInitialized(*synonyms[0]);
    if (!isTableInitialized) {
        initializeTable(context, synonyms);
    } else {
        updateTable(context, synonyms);
    }
}


// ai-gen end