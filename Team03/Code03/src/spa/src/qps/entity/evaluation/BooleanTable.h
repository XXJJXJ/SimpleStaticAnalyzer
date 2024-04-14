#ifndef BOOLEAN_TABLE_H
#define BOOLEAN_TABLE_H

#include "BaseTable.h"
#include <memory>

class BooleanTable : public BaseTable {
private:
    bool value;

public:
    explicit BooleanTable(const BaseTable &table);
    explicit BooleanTable(bool value);
    [[nodiscard]] bool getValue() const { return value; }
    std::shared_ptr<BaseTable> join(BaseTable &other) override;

    bool isEmpty() const override;
    bool isTrue() const;
    bool isBoolean() const override;
    bool operator==(const BaseTable &other) const override;
    virtual shared_ptr<BaseTable> filter(RowFilter &filter) const override;
    virtual shared_ptr<BaseTable> filter(std::function<bool(const std::vector<std::shared_ptr<Entity>> &)> predicate) const override;
    unordered_set<string> toStrings() override;
    unordered_set<string> toAttributeStrings(vector<shared_ptr<AttributeExtractor>> extractors) override;
    std::shared_ptr<BaseTable> negate();
};

#endif // BOOLEAN_TABLE_H
