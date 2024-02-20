// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a

#include "TableRow.h"

// Implementation of TableRow
TableRow::TableRow(const vector<shared_ptr<Entity>>& values) : values(values) {}

const vector<shared_ptr<Entity>>& TableRow::getValues() const {
    return values;
}

bool TableRow::operator==(const TableRow& other) const {
    return values == other.values;
}
// ai-gen end