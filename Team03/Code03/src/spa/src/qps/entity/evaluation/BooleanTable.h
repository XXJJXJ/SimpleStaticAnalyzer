#ifndef BOOLEAN_TABLE_H
#define BOOLEAN_TABLE_H

#include "BaseTable.h"
#include <memory>

class BooleanTable : public BaseTable {
private:
    bool value;

public:
    explicit BooleanTable(const BaseTable& table);
    [[nodiscard]] bool getValue() const { return value; }
    std::shared_ptr<BaseTable> join(BaseTable& other) override;
    bool isEmpty() const override;
    bool isTrue() const;
    bool isBoolean() const override;
    bool operator==(const BaseTable& other) const override;
};

#endif // BOOLEAN_TABLE_H
