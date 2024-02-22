// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <unordered_map>
#include "qps/entity/query/Synonym.h" // Assuming Synonym and Entity classes are defined elsewhere
#include "common/Entity.h"
#include "qps/entity/evaluation/TableRow.h"

using namespace std;

// Class to represent the table itself.
class Table {
private:
    std::vector<Synonym> headers;
    std::unordered_map<Synonym, int> headerIndexMap; // Mapping from synonym to index
    std::vector<TableRow> rows;

public:
    Table() = default;
    void addRow(const TableRow& row);
    void setHeaders(const vector<Synonym>& headers);
    [[nodiscard]] const vector<Synonym>& getHeaders() const;
    [[nodiscard]] Table selectColumns(const vector<Synonym>& synonyms) const; // Projection operation
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] vector<string> toStrings() const;
    [[nodiscard]] int getSize() const;
    shared_ptr<Table> join(Table& other);

    void updateHeaderIndexMap(); // Utility function to update headerIndexMap
    int indexOf(const Synonym& synonym) const; // Get index of a synonym
    bool hasHeader(const Synonym& synonym) const; // Check if a header exists

};

#endif // TABLE_H

// ai-gen end