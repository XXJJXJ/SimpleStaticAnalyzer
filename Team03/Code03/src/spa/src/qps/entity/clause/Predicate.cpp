#include "Predicate.h"

bool Predicate::isValidRow(const vector<shared_ptr<Entity>>& row) const {
    if (row.size() != validators.size()) {
        throw QPSEvaluationException("Predicate: mismatch between row size and row filter size, row size: "
        + to_string(row.size()) + ", row filter size: " + to_string(validators.size()));
    }
    for (int i = 0; i < row.size(); i++) {
        if (!validators[i]->passFilter(row[i])) {
            return false;
        }
    }
    return true;
}

std::string Predicate::toString() const {
    return "Predicate";
}

std::shared_ptr<BaseTable> Predicate::getResultTable(QueryManager& qm) {

    // Step 1: Fetch the full table, depending on the type of predicate
    auto fullTable = getFullTable(qm);

    // Step 2: Filter based on the validators
    auto filteredTable = fullTable->filter([this](const std::vector<std::shared_ptr<Entity>>& row) {
        return isValidRow(row);
    });

    // Step 3: Project to keep columns associated with a Synonym or determine a boolean result
    shared_ptr<BaseTable> resultTable = filteredTable->project(projectionFilter);

    // Step 4: construct result, adding synonyms if needed
    resultTable = TableFactory::createTable(synonyms, *resultTable);
    return resultTable;
}

// TODO: further refactor to remove duplication. One possible solution is to create wrapper classes for each of the
//  refs, and use template function. Currently we can't use template function because the refs are variants and C++
//  doesn't know how to handle them.
void Predicate::addStmtRef(StatementRef &stmtRef) {
    this->validators.push_back(getValidatorForStatementRef(stmtRef));
    if (std::holds_alternative<Synonym>(stmtRef)) {
        auto synonym = std::get<Synonym>(stmtRef);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
        this->projectionFilter.push_back(true);
    } else {
        this->projectionFilter.push_back(false);
    }
}

void Predicate::addEntityRef(EntityRef &entityRef) {
    this->validators.push_back(getValidatorForEntityRef(entityRef));
    if (std::holds_alternative<Synonym>(entityRef)) {
        auto synonym = std::get<Synonym>(entityRef);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
        this->projectionFilter.push_back(true);
    } else {
        this->projectionFilter.push_back(false);
    }
}

void Predicate::addProcAndStmtRef(ProcAndStmtRef &procAndStmtRef) {
    this->validators.push_back(getValidatorForProcAndStmtRef(procAndStmtRef));
    if (std::holds_alternative<Synonym>(procAndStmtRef)) {
        auto synonym = std::get<Synonym>(procAndStmtRef);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
        this->projectionFilter.push_back(true);
    } else {
        this->projectionFilter.push_back(false);
    }
}