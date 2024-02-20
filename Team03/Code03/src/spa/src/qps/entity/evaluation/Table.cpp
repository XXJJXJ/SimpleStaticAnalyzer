// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
#include "Table.h"


// Implementation of Table
void Table::addRow(const TableRow& row) {
    rows.push_back(row);
}

void Table::setHeaders(const vector<Synonym>& headers) {
    this->headers = headers;
}

const vector<Synonym>& Table::getHeaders() const {
    return headers;
}

Table Table::selectColumns(const vector<Synonym>& synonyms) const {
    Table newTable;
    vector<Synonym> newHeaders;
    vector<int> indices;

    // Find the indices of the selected synonyms in the current headers
    for (const auto& syn : synonyms) {
        for (size_t i = 0; i < headers.size(); ++i) {
            if (headers[i] == syn) {
                newHeaders.push_back(syn);
                indices.push_back(i);
                break;
            }
        }
    }

    newTable.setHeaders(newHeaders);

    // Project rows to new table based on selected columns
    for (const auto& row : rows) {
        vector<shared_ptr<Entity>> newRowValues;
        for (int idx : indices) {
            newRowValues.push_back(row.getValues()[idx]);
        }
        newTable.addRow(TableRow(newRowValues));
    }

    return newTable;
}

// ai-gen end