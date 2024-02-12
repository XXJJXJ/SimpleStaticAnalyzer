// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/b4e5ee0e-2ffc-4b9b-810c-871f71f82758

#include "ProjectionStrategy.h"
#include <algorithm>

ProjectionStrategy::ProjectionStrategy(std::shared_ptr<Synonym> synonym) : targetSynonym(std::move(synonym)) {}

void ProjectionStrategy::execute(QueryEvaluationContext &context) {
    if (!context.containsSynonym(*targetSynonym)) {
        return; // If the target synonym is not present, no action is needed.
    }

    auto targetSynonymValues = context.getSynonymValues(*targetSynonym);

    std::list<SynonymValues> updatedList;
    updatedList.push_back(targetSynonymValues); // Add only the target synonym values to the list.

    // Replace the existing list with the updated one.
    context.clearSynonymValuesList();
    for (const auto& synonymValues : updatedList) {
        context.addSynonymValues(synonymValues);
    }
}
// ai-gen end