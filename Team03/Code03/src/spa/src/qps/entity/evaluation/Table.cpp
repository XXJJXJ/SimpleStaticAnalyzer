// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
// prompt: https://chat.openai.com/share/eadbc02c-9e25-4f11-b2bb-c215c525d944
#include "Table.h"
#include <algorithm>
#include <unordered_set>
#include <memory>

bool rowsAreCompatible(const TableRow& row1, const TableRow& row2,
                       const Table& table1, const Table& table2,
                       const std::vector<Synonym>& commonHeaders);

std::vector<std::shared_ptr<Entity>> createJoinedRow(
        const TableRow& row1, const TableRow& row2,
        const std::vector<Synonym>& headers1, const std::vector<Synonym>& headers2,
        const std::vector<Synonym>& newHeaders
);

std::vector<std::shared_ptr<Entity>> createJoinedRow(const TableRow& row1, const TableRow& row2,
                                                     const Table& table1, const Table& table2,
                                                     const std::vector<Synonym>& newHeaders);

// Implementation of Table
void Table::addRow(const TableRow& row) {
    rows.push_back(row);
}

void Table::setHeaders(const vector<Synonym>& headers) {
    this->headers = headers;
    updateHeaderIndexMap();
}

const vector<Synonym>& Table::getHeaders() const {
    return headers;
}

Table Table::selectColumns(const vector<Synonym>& synonyms) const {
    Table newTable;
    vector<Synonym> newHeaders;
    vector<int> indices;

    // Find the indices of the selected synonyms in the current headers
    for (const auto& syn : synonyms) {
        for (size_t i = 0; i < headers.size(); ++i) {
            if (headers[i] == syn) {
                newHeaders.push_back(syn);
                indices.push_back(i);
                break;
            }
        }
    }

    newTable.setHeaders(newHeaders);

    // Project rows to new table based on selected columns
    for (const auto& row : rows) {
        vector<shared_ptr<Entity>> newRowValues;
        for (int idx : indices) {
            newRowValues.push_back(row.getValues()[idx]);
        }
        newTable.addRow(TableRow(newRowValues));
    }

    return newTable;
}

bool Table::isEmpty() const {
    return rows.empty();
}

vector<string> Table::toStrings() const {
    vector<string> rowStrings;
    rowStrings.reserve(rows.size());
    for (const TableRow& row : rows) {
        rowStrings.push_back(row.toString()); // Call toString on each TableRow and add to the vector
    }
    return rowStrings;
}

int Table::getSize() const {
    return rows.size();
}

// ai-gen end

std::shared_ptr<Table> Table::join(Table& other) {
    auto resultTable = std::make_shared<Table>();

    // Combine headers and identify common headers
    std::unordered_set<Synonym> headersSet1(this->headers.begin(), this->headers.end());
    std::vector<Synonym> newHeaders(this->headers.begin(), this->headers.end());
    std::vector<Synonym> commonHeaders;

    for (const auto& header : other.headers) {
        if (headersSet1.find(header) == headersSet1.end()) {
            newHeaders.push_back(header); // Add unique headers from 'other' table
        } else {
            commonHeaders.push_back(header); // Identify common headers
        }
    }

    resultTable->setHeaders(newHeaders);

    // Join rows based on common headers
    for (auto& row1 : this->rows) {
        for (auto& row2 : other.rows) {
            if (rowsAreCompatible(row1, row2, *this, other, commonHeaders)) {
                auto newValues = createJoinedRow(row1, row2, *this, other, newHeaders);
                resultTable->addRow(TableRow(newValues));
            }
        }
    }

    return resultTable;
}


bool rowsAreCompatible(const TableRow& row1, const TableRow& row2,
                       const Table& table1, const Table& table2,
                       const std::vector<Synonym>& commonHeaders) {
    for (const auto& commonHeader : commonHeaders) {
        int pos1 = table1.indexOf(commonHeader);
        int pos2 = table2.indexOf(commonHeader);
        if (*row1.getByIndex(pos1) != *row2.getByIndex(pos2)) {
            return false;
        }
    }
    return true;
}

std::vector<std::shared_ptr<Entity>> createJoinedRow(const TableRow& row1, const TableRow& row2,
                                                     const Table& table1, const Table& table2,
                                                     const std::vector<Synonym>& newHeaders) {
    std::vector<std::shared_ptr<Entity>> newValues;
    for (const auto& header : newHeaders) {
        if (table1.hasHeader(header)) {
            newValues.push_back(row1.getByIndex(table1.indexOf(header)));
        } else {
            if (table2.hasHeader(header)) {
                newValues.push_back(row2.getByIndex(table2.indexOf(header)));
            }
        }
    }
    return newValues;
}


void Table::updateHeaderIndexMap() {
    headerIndexMap.clear();
    for (int i = 0; i < headers.size(); ++i) {
        headerIndexMap[headers[i]] = i;
    }
}

int Table::indexOf(const Synonym& synonym) const {
    auto it = headerIndexMap.find(synonym);
    if (it != headerIndexMap.end()) {
        return it->second;
    }
    return -1; // Indicate not found
}

bool Table::hasHeader(const Synonym &synonym) const {
    return headerIndexMap.find(synonym) != headerIndexMap.end();
}
