#include "NotPredicate.h"

#include <utility>

NotPredicate::NotPredicate(shared_ptr<Predicate> predicate) {
    this->predicate = std::move(predicate);
    this->synonyms = this->predicate->getSynonyms();
}

/**
 * Overrides the general getResultTable logic for NotPredicate.
 * Steps:
 *     1. Get the result table of the predicate.
 *     2. If the result table is boolean, return the negation of the result table.
 *     3. Else, obtain the complementary table.
 */
std::shared_ptr<BaseTable> NotPredicate::getResultTable(QueryManager &qm) {
    auto resultTable = predicate->getResultTable(qm);

    // if result table is boolean, return the negation of the result table
    if (resultTable->isBoolean()) {
        auto boolTable = dynamic_pointer_cast<BooleanTable>(resultTable);
        return boolTable->negate();
    }

    // else, obtain the complementary table
    auto headerTable = dynamic_pointer_cast<HeaderTable>(resultTable);
    if (headerTable == nullptr) {
        throw QPSEvaluationException("NotPredicate::getResultTable: resultTable is not a HeaderTable/BooleanTable");
    }
    return headerTable->getComplement(qm);
}
