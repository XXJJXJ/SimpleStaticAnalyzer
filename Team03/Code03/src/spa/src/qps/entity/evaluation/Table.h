// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include "qps/entity/query/Synonym.h" // Assuming Synonym and Entity classes are defined elsewhere
#include "common/Entity.h"
#include "qps/entity/evaluation/TableRow.h"

using namespace std;

// Class to represent the table itself.
class Table {
private:
    vector<Synonym> headers; // The table headers (synonyms)
    vector<TableRow> rows; // The rows of the table

public:
    Table() = default;
    void addRow(const TableRow& row);
    void setHeaders(const vector<Synonym>& headers);
    [[nodiscard]] const vector<Synonym>& getHeaders() const;
    [[nodiscard]] Table selectColumns(const vector<Synonym>& synonyms) const; // Projection operation
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] vector<string> toStrings() const;
};

#endif // TABLE_H

// ai-gen end