#ifndef BASE_TABLE_H
#define BASE_TABLE_H

#include <vector>
#include <memory>
#include <functional>
#include "common/Entity.h"
#include "TableRow.h"
#include <functional>
#include "qps/entity/query/Synonym.h"

class BaseTable {
private:
    std::vector<TableRow> rows;
    int columnCount = 0; // Add columnCount field
    virtual bool isValidRow(const TableRow& row) const;

protected:
    virtual void makeRowsUnique();

public:
    BaseTable() = default;
    explicit BaseTable(const std::vector<std::vector<std::shared_ptr<Entity>>> &entities, int columnCount);

    void addRow(const TableRow& row);
    [[nodiscard]] virtual bool isEmpty() const;
    [[nodiscard]] int getSize();
    //[[nodiscard]] std::vector<std::string> toStrings();
    std::unordered_set<std::string> BaseTable::toStrings();
    shared_ptr<BaseTable> filter(std::function<bool(const std::vector<std::shared_ptr<Entity>>&)> predicate) const;
    shared_ptr<BaseTable> project(const std::vector<bool>& columnMask) const; // Projection function
    shared_ptr<BaseTable> addHeader(const std::vector<std::shared_ptr<Synonym>>& synonyms) const;
    const vector<TableRow> getRows() const;
    int getColumnCount() const;
    void setColumnCount(int count);
    void clearRows();
    virtual bool isBoolean() const;
    virtual shared_ptr<BaseTable> join(BaseTable& other);

    virtual ~BaseTable() = default;

    vector<TableRow> &getRows();

    virtual bool operator==(const BaseTable& other) const;


};
#endif // BASE_TABLE_H
