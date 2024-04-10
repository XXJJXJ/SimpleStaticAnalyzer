#include "Predicate.h"

void Predicate::addEntityRef(EntityRef &entityRef) {
    this->cellFilters.push_back(getFilterForEntityRef(entityRef));
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
    if (row.size() != cellFilters.size()) {
        throw QPSEvaluationException("Predicate: mismatch between row size and row filter size, row size: "
        + to_string(row.size()) + ", row filter size: " + to_string(cellFilters.size()));
    }
    for (int i = 0; i < row.size(); i++) {
        if (!cellFilters[i]->passFilter(row[i])) {
            return false;
        }
    }
    return true;
}

void Predicate::addStmtRef(StatementRef &stmtRef) {
    this->cellFilters.push_back(getFilterForStatementRef(stmtRef));
    if (std::holds_alternative<Synonym>(stmtRef)) {
        auto synonym = std::get<Synonym>(stmtRef);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
        this->projectionFilter.push_back(true);
    } else {
        this->projectionFilter.push_back(false);
    }
}


std::shared_ptr<BaseTable> Predicate::getResultTable(QueryEvaluationContext &qec) {

    auto qm = qec.getQueryManager();
    auto cache = qec.getCache();

    // Step 1: Fetch the full table, depending on the type of predicate
    shared_ptr<BaseTable> fullTable;
    if (cache->hasResult(this->getType())) {
        fullTable = cache->getResult(this->getType());
    } else {
        fullTable = getFullTable(*qm);
        cache->storeResult(this->getType(), fullTable);
    }

    // Step 2: Filter based on the cellFilters / rowFilters
    auto filteredTable = fullTable->filter([this](const std::vector<std::shared_ptr<Entity>>& row) {
        return isValidRow(row);
    });

    for (const auto& rowFilter : rowFilters) {
        filteredTable = filteredTable->filter(*rowFilter);
    }

    // Step 3: Project to keep columns associated with a Synonym or determine a boolean result
    shared_ptr<BaseTable> resultTable = filteredTable->project(projectionFilter);

    // Step 4: construct result, adding synonyms if needed
    resultTable = TableFactory::createTable(synonyms, *resultTable);
    return resultTable;
}

void Predicate::addProcAndStmtRef(ProcAndStmtRef &procAndStmtRef) {
    this->cellFilters.push_back(getFilterForProcAndStmtRef(procAndStmtRef));
    if (std::holds_alternative<Synonym>(procAndStmtRef)) {
        auto synonym = std::get<Synonym>(procAndStmtRef);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
        this->projectionFilter.push_back(true);
    } else {
        this->projectionFilter.push_back(false);
    }
}
void Predicate::addRef(Ref &ref) {
    if (ref.holdsSynonym()) {
        auto synonym = ref.getSynonym();
        this->synonyms.push_back(synonym);
        this->projectionFilter.push_back(true);
        this->cellFilters.push_back(getFilterForRef(ref));
    }
}

PredicateType Predicate::getType() const {
    return PredicateType::Unknown;
}

void Predicate::addRowFilter(RowFilter &rowFilter) {
    this->rowFilters.push_back(std::make_shared<RowFilter>(rowFilter));
}

size_t Predicate::hash() const {
    return 0; // not used
}

bool Predicate::equals(const Predicate& other) const {
    return true; // not used
}