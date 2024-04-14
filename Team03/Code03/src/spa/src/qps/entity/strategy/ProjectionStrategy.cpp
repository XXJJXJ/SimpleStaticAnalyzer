// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/b4e5ee0e-2ffc-4b9b-810c-871f71f82758
// prompt 2: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a

#include "ProjectionStrategy.h"
#include <algorithm>
#include "qps/entity/evaluation/HeaderTable.h"

ProjectionStrategy::ProjectionStrategy(vector<std::shared_ptr<Synonym>> synonyms)
    : targetSynonyms(std::move(synonyms)) {}

void ProjectionStrategy::execute(QueryEvaluationContext &context) {
    // Select boolean case
    if (targetSynonyms.empty()) {
        context.setResultTable(std::make_shared<BooleanTable>(!context.isCurrentResultEmpty()));
        return;
    }
    // Short-circuiting for empty result
    if (context.isCurrentResultEmpty()) {
        HeaderTable emptyTable;
        // Convert targetSynonyms to the format expected by setHeaders
        emptyTable.setHeaders(targetSynonyms);
        context.setResultTable(std::make_shared<HeaderTable>(emptyTable));
        return;
    }

    // Get the projected tables
    auto projectedTables = getProjectedTables(context);

    // Get the cross product for the projected tables
    shared_ptr<BaseTable> resultTable = projectedTables[0];
    for (size_t i = 1; i < projectedTables.size(); ++i) {
        resultTable = resultTable->join(*projectedTables[i]);
    }

    // Reorder the headers to match the order of the target synonyms
    shared_ptr<HeaderTable> resultHeaderTable = std::dynamic_pointer_cast<HeaderTable>(resultTable);
    if (!resultHeaderTable) {
        throw QPSEvaluationException("Projection strategy: result table is not a header table unexpectedly");
    }
    resultHeaderTable = make_shared<HeaderTable>(resultHeaderTable->selectColumns(targetSynonyms));
    context.setResultTable(resultHeaderTable);
}

vector<SynonymPtrSet> ProjectionStrategy::groupTargetSynonyms(QueryEvaluationContext &context) const {
    // Get the synonym groups from the context
    auto synonymGroups = context.getSynonymGroups();

    // This will hold the mapping of groups to their synonyms
    std::vector<SynonymPtrSet> groupsToTargetSynonyms;

    // Initialize groupsToTargetSynonyms with empty sets for each group
    for (size_t i = 0; i < synonymGroups.size(); ++i) {
        groupsToTargetSynonyms.emplace_back();
    }

    // Iterate over each target synonym
    for (const auto &targetSynonym : targetSynonyms) {
        // Check which group this synonym belongs to
        for (size_t i = 0; i < synonymGroups.size(); ++i) {
            if (synonymGroups[i].find(targetSynonym) != synonymGroups[i].end()) {
                // If the synonym is found in the current group, add it to the corresponding set
                groupsToTargetSynonyms[i].insert(targetSynonym);
                break; // Move to the next target synonym as each synonym belongs to only one group
            }
        }
    }
    return groupsToTargetSynonyms;
}

std::vector<shared_ptr<HeaderTable>> ProjectionStrategy::getProjectedTables(QueryEvaluationContext &context) {
    // First, group the target synonyms using the helper function
    auto groupsToTargetSynonyms = groupTargetSynonyms(context);

    std::vector<shared_ptr<HeaderTable>> projectedTables;

    // Iterate over each group
    for (const auto &group : groupsToTargetSynonyms) {
        // Skip empty groups
        if (group.empty()) continue;

        // Get the table for the group
        std::shared_ptr<HeaderTable> tableForGroup = context.getTableForSynonym(**group.begin());
        if (!tableForGroup) {
            throw QPSEvaluationException("Projection strategy: cannot find table for synonym in group");
        }

        HeaderTable projectedTable = tableForGroup->selectColumns({group.begin(), group.end()});

        // Add the projected table to the vector
        projectedTables.push_back(make_shared<HeaderTable>(projectedTable));
    }

    return projectedTables;
}
// ai-gen end