#include "BaseTable.h"
#include <algorithm>
#include "TableRow.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "BooleanTable.h"

BaseTable::BaseTable(const std::vector<std::vector<std::shared_ptr<Entity>>>& entities) {
    if (!entities.empty()) {
        columnCount = static_cast<int>(entities.front().size()); // Initialize columnCount based on the first row
    }
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

int BaseTable::getSize() const {
    return static_cast<int>(rows.size());
}

std::vector<std::string> BaseTable::toStrings() const {
    std::vector<std::string> rowStrings;
    rowStrings.reserve(rows.size());
    std::transform(rows.begin(), rows.end(), std::back_inserter(rowStrings),
                   [](const TableRow& row) { return row.toString(); });
    return rowStrings;
}

shared_ptr<BaseTable> BaseTable::filter(std::function<bool(const std::vector<std::shared_ptr<Entity>>&)> predicate) const {
    std::vector<std::vector<std::shared_ptr<Entity>>> filteredEntities;

    for (const auto& row : rows) {
        if (predicate(row.getValues())) {
            filteredEntities.push_back(row.getValues());
        }
    }

    return std::make_shared<BaseTable>(filteredEntities);
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
    return std::make_shared<BaseTable>(projectedEntities);
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
