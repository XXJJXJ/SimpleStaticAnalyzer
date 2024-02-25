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
#include "BaseTable.h"

using namespace std;

// Class to represent the table itself.
class HeaderTable : public BaseTable {
private:
    std::vector<shared_ptr<Synonym>> headers;
    std::unordered_map<Synonym, int> headerIndexMap; // Mapping from synonym to index
    bool isValidRow(const TableRow& row) const override;

public:
    HeaderTable() = default;
    HeaderTable(const vector<shared_ptr<Synonym>>& headers, const vector<vector<shared_ptr<Entity>>>& entities);
    HeaderTable(const vector<shared_ptr<Synonym>>& headers, BaseTable& baseTable);
    void setHeaders(const vector<shared_ptr<Synonym>>& headers);
    [[nodiscard]] const vector<shared_ptr<Synonym>>& getHeaders() const;
    [[nodiscard]] HeaderTable selectColumns(const vector<shared_ptr<Synonym>>& synonyms) const; // Projection operation
    shared_ptr<BaseTable> join(BaseTable& other) override;

    void updateHeaderIndexMap(); // Utility function to update headerIndexMap
    int indexOf(const Synonym& synonym) const; // Get index of a synonym
    bool hasHeader(const Synonym& synonym) const; // Check if a header exists
};

#endif // TABLE_H

// ai-gen end