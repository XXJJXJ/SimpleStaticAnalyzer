// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/b4e5ee0e-2ffc-4b9b-810c-871f71f82758
// prompt 2: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a

#include "ProjectionStrategy.h"
#include <algorithm>

ProjectionStrategy::ProjectionStrategy(std::shared_ptr<Synonym> synonym) : targetSynonym(std::move(synonym)) {}

void ProjectionStrategy::execute(QueryEvaluationContext &context) {
    // Check all tables in the context; if any is empty, return an empty table directly.
    if (context.isResultEmpty()) {
        HeaderTable emptyTable;
        emptyTable.setHeaders({*targetSynonym});
        context.setResultTable(std::make_shared<HeaderTable>(emptyTable));
        return;
    }

    // Proceed if no empty tables are found
    auto table = context.getTableForSynonym(*targetSynonym);
    if (!table) {
        // Synonym not used in constructing tables, query QueryManager for entities by type
        auto entities = context.getQueryManager()->getAllEntitiesByType(targetSynonym->getType());
        HeaderTable newTable;
        newTable.setHeaders({*targetSynonym}); // Assuming setHeaders method exists

        for (const auto& entity : entities) {
            // Convert entity to TableRow and add to newTable
            // This step assumes you have a mechanism to convert an Entity to a TableRow
            newTable.addRow(TableRow({entity}));
        }

        context.setResultTable(std::make_shared<HeaderTable>(newTable));
    } else {
        // If the synonym's table exists and is not empty, select the column and project it.
        HeaderTable projectedTable = table->selectColumns({*targetSynonym});
        context.setResultTable(std::make_shared<HeaderTable>(projectedTable));
    }
}
// ai-gen end