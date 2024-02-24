#ifndef BASE_TABLE_H
#define BASE_TABLE_H

#include <vector>
#include <memory>
#include "common/Entity.h"
#include "TableRow.h"

class BaseTable {
protected:
    std::vector<TableRow> rows;

public:
    BaseTable() = default;
    explicit BaseTable(const std::vector<std::vector<std::shared_ptr<Entity>>>& entities);

    void addRow(const TableRow& row);
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] std::vector<std::string> toStrings() const;

    // Virtual destructor to ensure derived class destructors are called
    virtual ~BaseTable() = default;
};

#endif // BASE_TABLE_H
