// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
// prompt: https://chat.openai.com/share/eadbc02c-9e25-4f11-b2bb-c215c525d944
#include "HeaderTable.h"
#include <algorithm>
#include <unordered_set>
#include <memory>
#include <set>
#include <map>
#include "common/spa_exception/QPSEvaluationException.h"
#include "BooleanTable.h"

bool rowsAreCompatible(const TableRow &row1, const TableRow &row2,
                       const HeaderTable &table1, const HeaderTable &table2,
                       const std::vector<shared_ptr<Synonym>> &commonHeaders);


std::vector<std::shared_ptr<Entity>> createJoinedRow(const TableRow &row1, const TableRow &row2,
                                                     const HeaderTable &table1, const HeaderTable &table2,
                                                     const std::vector<shared_ptr<Synonym>> &newHeaders);


bool HeaderTable::isValidRow(const TableRow &row) const {
    if (row.getValues().size() == headers.size()) {
        // Checks if the types of the entities in the row match the types of the headers
        for (size_t i = 0; i < headers.size(); ++i) {
            if (!row.getValues()[i]->isOfType(headers[i]->getType())) {
                return false;
            }
        }
    }
    return row.getValues().size() == headers.size();
}

void HeaderTable::setHeaders(const vector<shared_ptr<Synonym>> &headers) {
    this->headers = headers;
    setColumnCount(headers.size());
    updateHeaderIndexMap();
}

const vector<shared_ptr<Synonym>>& HeaderTable::getHeaders() const {
    return headers;
}

HeaderTable HeaderTable::selectColumns(const vector<shared_ptr<Synonym>> &synonyms) const {
    HeaderTable newTable;
    vector<shared_ptr<Synonym>> newHeaders;
    vector<int> indices;

    // Find the indices of the selected synonyms in the current headers
    for (const auto &syn: synonyms) {
        for (size_t i = 0; i < headers.size(); ++i) {
            if (*headers[i] == *syn) {
                newHeaders.push_back(syn);
                indices.push_back(i);
                break;
            }
        }
    }

    newTable.setHeaders(newHeaders);

    // Project rows to new table based on selected columns
    for (const auto &row: getRows()) {
        vector<shared_ptr<Entity>> newRowValues;
        for (int idx: indices) {
            newRowValues.push_back(row.getValues()[idx]);
        }
        newTable.addRow(TableRow(newRowValues));
    }

    return newTable;
}


// ai-gen end

std::shared_ptr<HeaderTable> HeaderTable::crossJoin(BaseTable &other) {
    auto resultTable = std::make_shared<HeaderTable>();
    auto otherHeader = dynamic_cast<HeaderTable *>(&other);

    if (otherHeader) {
        std::vector<std::shared_ptr<Synonym>> newHeaders(this->headers);
        newHeaders.insert(newHeaders.end(), otherHeader->headers.begin(), otherHeader->headers.end());
        resultTable->setHeaders(newHeaders);

        // Cross join rows
        for (auto& row1 : this->getRows()) {
            for (auto& row2 : other.getRows()) {
                auto newValues = row1.getValues();
                newValues.insert(newValues.end(), row2.getValues().begin(), row2.getValues().end());
                resultTable->addRow(TableRow(newValues));
            }
        }
    } else if (auto otherBoolean = dynamic_cast<BooleanTable *>(&other)) {
        // If the BooleanTable represents false, return an empty table
        if (!otherBoolean->isTrue()) {
            return std::make_shared<HeaderTable>();
        } else {
            // If true, return a copy of the current table
            resultTable = std::make_shared<HeaderTable>(*this);
        }
    } else {
        throw QPSEvaluationException("HeaderTable::crossJoin: other is not a HeaderTable or a BooleanTable");
    }

    return resultTable;
}

std::shared_ptr<BaseTable> HeaderTable::join(BaseTable &other) {
    auto resultTable = std::make_shared<HeaderTable>();
    auto otherHeader = dynamic_cast<HeaderTable *>(&other);

    if (otherHeader) {
        std::unordered_set<std::shared_ptr<Synonym>, SynonymPtrHash, SynonymPtrEqual> headersSet1(this->headers.begin(), this->headers.end());
        std::vector<std::shared_ptr<Synonym>> newHeaders(this->headers);
        std::vector<std::shared_ptr<Synonym>> commonHeaders;

        // Assuming getHeaders returns vector<shared_ptr<Synonym>>
        for (const auto &header : otherHeader->getHeaders()) {
            if (headersSet1.find(header) == headersSet1.end()) {
                newHeaders.push_back(header); // Add unique headers from 'other' table
            } else {
                commonHeaders.push_back(header); // Identify common headers
            }
        }

        resultTable->setHeaders(newHeaders);

        // Join rows based on common headers
        for (auto& row1 : this->getRows()) {
            for (auto& row2 : other.getRows()) {
                if (rowsAreCompatible(row1, row2, *this, *otherHeader, commonHeaders)) {
                    auto newValues = createJoinedRow(row1, row2, *this, *otherHeader, newHeaders);
                    resultTable->addRow(TableRow(newValues));
                }
            }
        }
    } else if (auto otherBoolean = dynamic_cast<BooleanTable *>(&other)) {
        // If the BooleanTable represents false, clear rows of the current table
        if (!otherBoolean->isTrue()) {
            resultTable->clearRows(); // Assuming HeaderTable has a method to clear rows
        } else {
            // If true, return a copy of the current table
            resultTable = std::make_shared<HeaderTable>(*this);
//            resultTable->makeRowsUnique();
        }
    } else {
        throw QPSEvaluationException("HeaderTable::join: other is not a HeaderTable or a BooleanTable");
    }

    return resultTable;
}


bool rowsAreCompatible(const TableRow &row1, const TableRow &row2,
                       const HeaderTable &table1, const HeaderTable &table2,
                       const std::vector<shared_ptr<Synonym>> &commonHeaders) {
    for (const auto &commonHeader: commonHeaders) {
        int pos1 = table1.indexOf(*commonHeader);
        int pos2 = table2.indexOf(*commonHeader);
        if (*row1.getByIndex(pos1) != *row2.getByIndex(pos2)) {
            return false;
        }
    }
    return true;
}

std::vector<std::shared_ptr<Entity>> createJoinedRow(const TableRow &row1, const TableRow &row2,
                                                     const HeaderTable &table1, const HeaderTable &table2,
                                                     const std::vector<shared_ptr<Synonym>> &newHeaders) {
    std::vector<std::shared_ptr<Entity>> newValues;
    for (const auto &header: newHeaders) {
        if (table1.hasHeader(*header)) {
            newValues.push_back(row1.getByIndex(table1.indexOf(*header)));
        } else {
            if (table2.hasHeader(*header)) {
                newValues.push_back(row2.getByIndex(table2.indexOf(*header)));
            }
        }
    }
    return newValues;
}


void HeaderTable::updateHeaderIndexMap() {
    headerIndexMap.clear();
    for (int i = 0; i < headers.size(); ++i) {
        headerIndexMap[*headers[i]] = i;
    }
}

int HeaderTable::indexOf(const Synonym &synonym) const {
    auto it = headerIndexMap.find(synonym);
    if (it != headerIndexMap.end()) {
        return it->second;
    }
    throw QPSEvaluationException("HeaderTable::indexOf: Synonym not found in headers");
}

bool HeaderTable::hasHeader(const Synonym &synonym) const {
    return headerIndexMap.find(synonym) != headerIndexMap.end();
}

HeaderTable::HeaderTable(const vector<shared_ptr<Synonym>> &headers, const vector<vector<shared_ptr<Entity>>> &entities) {
    this->headers = headers;
    setColumnCount(headers.size());
    for (const auto &row: entities) {
        this->addRow(TableRow(row));
    }
    updateHeaderIndexMap();
}

HeaderTable::HeaderTable(const vector<shared_ptr<Synonym>> &headers, shared_ptr<BaseTable> baseTable) {
    if (headers.size() != baseTable->getColumnCount()) {
        throw QPSEvaluationException("HeaderTable: headers size does not match baseTable column count");
    }
    this->headers = headers;
    setColumnCount(headers.size());
    for (const auto &row: baseTable->getRows()) {
        this->addRow(row);
    }
    updateHeaderIndexMap();
}

bool HeaderTable::operator==(const BaseTable &other) const {
    if (auto otherHeader = dynamic_cast<const HeaderTable *>(&other)) {
        if (this->headers.size() != otherHeader->headers.size()) {
            return false;
        }
        for (size_t i = 0; i < this->headers.size(); ++i) {
            if (!(*this->headers[i] == *otherHeader->headers[i])) {
                return false;
            }
        }
        return BaseTable::operator==(other);
    }
    return false;
}

/**
 * Constructs a header table from a base table and a list of synonyms, with some additional checks:
 * - Filters rows where duplicated columns have mismatched values
 * - Merges duplicated columns into a single column
 */
std::shared_ptr<HeaderTable> HeaderTable::fromBaseTable(const BaseTable& baseTable, const vector<shared_ptr<Synonym>>& synonyms) {
    // Maps to track synonym occurrences and construct the projection mask
    std::unordered_map<std::shared_ptr<Synonym>, std::vector<int>, SynonymPtrHash, SynonymPtrEqual> synonymIndices;
    std::vector<shared_ptr<Synonym>> uniqueSynonyms;
    std::vector<bool> columnMask(baseTable.getColumnCount(), false); // Initialize with false

    // Populate synonymIndices and uniqueSynonyms, update columnMask for projection
    for (size_t i = 0; i < synonyms.size(); ++i) {
        if (synonymIndices.find(synonyms[i]) == synonymIndices.end()) {
            uniqueSynonyms.push_back(synonyms[i]);
            synonymIndices[synonyms[i]] = {static_cast<int>(i)};
            columnMask[i] = true; // Mark this column for inclusion
        } else {
            synonymIndices[synonyms[i]].push_back(static_cast<int>(i));
            // No need to mark additional columns for duplicates, as they will be merged
        }
    }

    // Filter rows where duplicated columns have mismatched values
    auto filteredTable = baseTable.filter([&](const std::vector<std::shared_ptr<Entity>>& row) -> bool {
        for (const auto& pair : synonymIndices) {
            const auto& indices = pair.second;
            if (indices.size() > 1) { // Only check duplicates
                std::shared_ptr<Entity> firstEntity = row[indices[0]];
                for (size_t i = 1; i < indices.size(); ++i) {
                    if (*row[indices[i]] != *firstEntity) {
                        return false; // Entities in duplicated columns don't match
                    }
                }
            }
        }
        return true;
    });

    // Use project function with the constructed columnMask to create the projected table
    auto projectedTable = filteredTable->project(columnMask);

    // Since project returns a BaseTable, we convert it to HeaderTable and set the unique headers
    auto headerTable = std::make_shared<HeaderTable>(uniqueSynonyms, projectedTable);
    return headerTable;
}

shared_ptr<BaseTable> HeaderTable::getComplement(QueryManager& qm) {
    // Get the full table of synonyms
    auto fullTable = getFullTable(this->headers, qm);

    // Get the complement of the current table
    auto currentRowSet = this->getRowSet();
    auto fullRowSet = fullTable->getRowSet();
    std::unordered_set<TableRow> complementRowSet;

    // Find the set difference
    for (const auto& row : fullRowSet) {
        if (currentRowSet.find(row) == currentRowSet.end()) {
            complementRowSet.insert(row);
        }
    }

    // Create a new HeaderTable from the complement row set
    auto complementTable = std::make_shared<HeaderTable>();
    complementTable->setHeaders(this->headers);
    for (const auto& row : complementRowSet) {
        complementTable->addRow(row);
    }
    return complementTable;

}

shared_ptr<HeaderTable> HeaderTable::getFullTable(const vector<shared_ptr<Synonym>>& synonyms, QueryManager &qm) {
    if (synonyms.empty()) {
        throw QPSEvaluationException("HeaderTable::getFullTable: Synonyms list is empty");
    }
    // Get the full table of synonyms
    vector<shared_ptr<HeaderTable>> fullTables;
    for (const auto &synonym: synonyms) {
        auto table = make_shared<HeaderTable>(synonym, qm.getAllEntitiesByType(synonym->getType()));
        fullTables.push_back(table);
    }

    // Join the full tables
    auto resultTable = fullTables[0];
    for (size_t i = 1; i < fullTables.size(); ++i) {
        resultTable = dynamic_pointer_cast<HeaderTable>(resultTable->join(*fullTables[i]));
    }

    // Select columns, to ensure that only the required synonyms are present in order
    resultTable = make_shared<HeaderTable>(resultTable->selectColumns(synonyms));

    return resultTable;
}

// Constructor for HeaderTable with single column, where each entity is a row
HeaderTable::HeaderTable(const shared_ptr<Synonym> &header, const vector<shared_ptr<Entity>> &entities) {
    this->headers = {header};
    setColumnCount(1);
    for (const auto &entity: entities) {
        this->addRow(TableRow({entity}));
    }
    updateHeaderIndexMap();
}
