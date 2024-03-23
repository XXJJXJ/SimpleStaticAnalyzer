#include "Predicate.h"

void Predicate::addEntityRef(EntityRef &entityRef) {
    this->rowFilter.push_back(getFilterForEntityRef(entityRef));
    if (std::holds_alternative<Synonym>(entityRef)) {
        auto synonym = std::get<Synonym>(entityRef);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
        this->projectionFilter.push_back(true);
    } else {
        this->projectionFilter.push_back(false);
    }
}

std::shared_ptr<BaseTable> Predicate::getFullTable(QueryManager &qm) {
    return {};
}

bool Predicate::isValidRow(const vector<shared_ptr<Entity>>& row) const {
    if (row.size() != rowFilter.size()) {
        throw QPSEvaluationException("Predicate: mismatch between row size and row filter size, row size: "
        + to_string(row.size()) + ", row filter size: " + to_string(rowFilter.size()));
    }
    for (int i = 0; i < row.size(); i++) {
        if (!rowFilter[i]->passFilter(row[i])) {
            return false;
        }
    }
    return true;
}

void Predicate::addStmtRef(StatementRef &stmtRef) {
    this->rowFilter.push_back(getFilterForStatementRef(stmtRef));
    if (std::holds_alternative<Synonym>(stmtRef)) {
        auto synonym = std::get<Synonym>(stmtRef);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
        this->projectionFilter.push_back(true);
    } else {
        this->projectionFilter.push_back(false);
    }
}


std::shared_ptr<BaseTable> Predicate::getResultTable(QueryManager& qm) {

    // Step 1: Fetch the full table, depending on the type of predicate
    auto fullTable = getFullTable(qm);

    // Step 2: Filter based on the rowFilter
    auto filteredTable = fullTable->filter([this](const std::vector<std::shared_ptr<Entity>>& row) {
        return isValidRow(row);
    });

    // Step 3: Project to keep columns associated with a Synonym or determine a boolean result
    shared_ptr<BaseTable> resultTable = filteredTable->project(projectionFilter);

    // Step 4: construct result, adding synonyms if needed
    resultTable = TableFactory::createTable(synonyms, *resultTable);
    return resultTable;
}

void Predicate::addProcAndStmtRef(ProcAndStmtRef &procAndStmtRef) {
    this->rowFilter.push_back(getFilterForProcAndStmtRef(procAndStmtRef));
    if (std::holds_alternative<Synonym>(procAndStmtRef)) {
        auto synonym = std::get<Synonym>(procAndStmtRef);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
        this->projectionFilter.push_back(true);
    } else {
        this->projectionFilter.push_back(false);
    }
}

