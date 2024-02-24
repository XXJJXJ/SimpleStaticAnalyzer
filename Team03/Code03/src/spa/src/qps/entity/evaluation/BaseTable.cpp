#include "BaseTable.h"
#include <algorithm> // For std::transform
#include "TableRow.h" // Include the correct header for your TableRow class

BaseTable::BaseTable(const std::vector<std::vector<std::shared_ptr<Entity>>>& entities) {
    for (const auto& rowEntities : entities) {
        this->addRow(TableRow(rowEntities));
    }
}

void BaseTable::addRow(const TableRow& row) {
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
