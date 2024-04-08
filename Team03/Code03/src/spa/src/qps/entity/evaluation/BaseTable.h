#ifndef BASE_TABLE_H
#define BASE_TABLE_H

#include <vector>
#include <memory>
#include <functional>
#include "common/Entity.h"
#include "TableRow.h"
#include <functional>
#include "qps/entity/query/Synonym.h"
#include "qps/entity/clause/attribute/AttributeExtractor.h"
#include "qps/entity/clause/attribute/NameExtractor.h"

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
    void append(const BaseTable& other);
    [[nodiscard]] virtual bool isEmpty() const;
    [[nodiscard]] int getSize();

    virtual std::unordered_set<std::string> toStrings();
    virtual std::unordered_set<std::string> toAttributeStrings(vector<shared_ptr<AttributeExtractor>> extractors);
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
    unordered_set<TableRow> getRowSet();

    virtual bool operator==(const BaseTable& other) const;


};
#endif // BASE_TABLE_H
