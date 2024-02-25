#ifndef BASE_TABLE_H
#define BASE_TABLE_H

#include <vector>
#include <memory>
#include "common/Entity.h"
#include "TableRow.h"

class BaseTable {
private:
    std::vector<TableRow> rows;
    int columnCount = 0; // Add columnCount field
    virtual bool isValidRow(const TableRow& row) const;

public:
    BaseTable() = default;
    explicit BaseTable(const std::vector<std::vector<std::shared_ptr<Entity>>>& entities);

    void addRow(const TableRow& row);
    [[nodiscard]] virtual bool isEmpty() const;
    [[nodiscard]] int getSize() const;
    [[nodiscard]] std::vector<std::string> toStrings() const;
    shared_ptr<BaseTable> filter(std::function<bool(const std::vector<std::shared_ptr<Entity>>&)> predicate) const;
    shared_ptr<BaseTable> project(const std::vector<bool>& columnMask) const; // Projection function
    const vector<TableRow> getRows() const;
    int getColumnCount() const;
    void setColumnCount(int count);
    void clearRows();
    virtual bool isBoolean() const;
    virtual shared_ptr<BaseTable> join(BaseTable& other);

    virtual ~BaseTable() = default;

    vector<TableRow> &getRows();
};
#endif // BASE_TABLE_H
