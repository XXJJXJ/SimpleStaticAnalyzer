// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
#ifndef SPA_TABLEROW_H
#define SPA_TABLEROW_H


#include "common/Entity.h"
#include <vector>
#include <memory>
#include <string>

// Class to represent a row in the table.
class TableRow {
private:
    vector<shared_ptr<Entity>> values; // Stores the values of the row

public:
    explicit TableRow(const vector<shared_ptr<Entity>>& v);
    [[nodiscard]] const vector<shared_ptr<Entity>>& getValues() const;
    bool operator==(const TableRow& other) const;
    friend class Table; // Allows Table to access private members of TableRow
};


#endif //SPA_TABLEROW_H

// ai-gen end