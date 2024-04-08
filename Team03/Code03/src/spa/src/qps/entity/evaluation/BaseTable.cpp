#include "BaseTable.h"
#include <algorithm>
#include "TableRow.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "BooleanTable.h"

// Must specify columnCount as entities could be empty.
BaseTable::BaseTable(const std::vector<std::vector<std::shared_ptr<Entity>>> &entities, int columnCount) {
    this->columnCount = columnCount;
    for (const auto& rowEntities : entities) {
        this->addRow(TableRow(rowEntities));
    }
}

void BaseTable::addRow(const TableRow& row) {
    if (!isValidRow(row)) {
        // Handle error: row does not match columnCount
        throw QPSEvaluationException("BaseTable::addRow: Row size does not match column count in table.");
    }
    rows.push_back(row);
}
bool BaseTable::isEmpty() const {
    return rows.empty();
}

int BaseTable::getSize() {
    makeRowsUnique();
    return static_cast<int>(rows.size());
}

//std::vector<std::string> BaseTable::toStrings() {
//    makeRowsUnique();
//    std::vector<std::string> rowStrings;
//    rowStrings.reserve(rows.size());
//    std::transform(rows.begin(), rows.end(), std::back_inserter(rowStrings),
//                   [](const TableRow& row) { return row.toString(); });
//    return rowStrings;
//}

std::unordered_set<std::string> BaseTable::toStrings() {
    makeRowsUnique();
    std::unordered_set<std::string> rowStrings;
    rowStrings.reserve(rows.size());
    for (const auto& row : rows) {
        auto result = rowStrings.insert(row.toString());
    }
    return rowStrings;
}

std::unordered_set<std::string> BaseTable::toAttributeStrings(vector<shared_ptr<AttributeExtractor>> extractors) {
    // If number of columns doesn't match, use name extractor as default value.
    if (extractors.size() != columnCount) {
        extractors.clear();
        extractors.resize(columnCount, std::make_shared<NameExtractor>());

    }
    makeRowsUnique();
    std::unordered_set<std::string> rowStrings;
    rowStrings.reserve(rows.size());
    for (const auto &row: rows) {
        auto result = rowStrings.insert(row.toAttributeString(extractors));
    }
    return rowStrings;
}

shared_ptr<BaseTable> BaseTable::filter(std::function<bool(const std::vector<std::shared_ptr<Entity>>&)> predicate) const {
    std::vector<std::vector<std::shared_ptr<Entity>>> filteredEntities;

    for (const auto& row : rows) {
        if (predicate(row.getValues())) {
            filteredEntities.push_back(row.getValues());
        }
    }

    return std::make_shared<BaseTable>(filteredEntities, columnCount);
}

// This should return either Boolean or BaseTable, depending on the columnMask
shared_ptr<BaseTable> BaseTable::project(const std::vector<bool>& columnMask) const {
    if (columnMask.size() != columnCount) {
        throw QPSEvaluationException("BaseTable::project: Column mask size does not match column count in table.");
    }

    // if columnMask is all false, return a Boolean table
    if (std::all_of(columnMask.begin(), columnMask.end(), [](bool b) { return !b; })) {
        return std::make_shared<BooleanTable>(*this);
    }

    int newColumnCount = std::count(columnMask.begin(), columnMask.end(), true);

    // else return a HeaderTable
    std::vector<std::vector<std::shared_ptr<Entity>>> projectedEntities;
    for (const auto& row : rows) {
        std::vector<std::shared_ptr<Entity>> newRow;
        for (size_t i = 0; i < columnMask.size(); ++i) {
            if (columnMask[i]) {
                newRow.push_back(row.getByIndex(i));
            }
        }
        projectedEntities.push_back(newRow);
    }
    return std::make_shared<BaseTable>(projectedEntities, newColumnCount);
}

bool BaseTable::isValidRow(const TableRow &row) const {
    return row.getValues().size() == columnCount;
}

std::vector<TableRow> &BaseTable::getRows() {
    return rows;
}

int BaseTable::getColumnCount() const {
    return columnCount;
}

void BaseTable::setColumnCount(int count) {
    columnCount = count;
}

void BaseTable::clearRows() {
    rows.clear();
}

bool BaseTable::isBoolean() const {
    return false;
}

shared_ptr<BaseTable> BaseTable::join(BaseTable &other) {
    throw QPSEvaluationException("BaseTable::join: Join operation not supported for BaseTable.");
}

const vector<TableRow> BaseTable::getRows() const {
    return rows;
}

bool BaseTable::operator==(const BaseTable &other) const {
    return rows == other.rows;
}

void BaseTable::makeRowsUnique() {
    // Sort rows to bring duplicates together
    std::sort(rows.begin(), rows.end(), [](const TableRow& a, const TableRow& b) {
        if (a.getValues().size() != b.getValues().size()) return a.getValues().size() < b.getValues().size();
        for (size_t i = 0; i < a.getValues().size(); ++i) {
            // Assuming Entity has a method to compare which defines a strict weak ordering
            if (*(a.getValues()[i]) != *(b.getValues()[i])) {
                return *(a.getValues()[i]) < *(b.getValues()[i]);
            }
        }
        return false; // Consider equal if all elements are equal
    });

    // Remove consecutive duplicates
    auto last = std::unique(rows.begin(), rows.end());
    rows.erase(last, rows.end());
}

unordered_set<TableRow> BaseTable::getRowSet() {
    return unordered_set<TableRow>(rows.begin(), rows.end());
}

void BaseTable::append(const BaseTable &other) {
    // Checks column count
    if (columnCount != other.columnCount) {
        throw QPSEvaluationException("BaseTable::append: Column count does not match.");
    }
    for (const auto& row : other.getRows()) {
        addRow(row);
    }
}


