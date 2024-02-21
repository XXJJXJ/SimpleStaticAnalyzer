// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
// prompt: https://chat.openai.com/share/eadbc02c-9e25-4f11-b2bb-c215c525d944

#include "TableRow.h"

// Implementation of TableRow
TableRow::TableRow(const vector<shared_ptr<Entity>>& values) : values(values) {}

const vector<shared_ptr<Entity>>& TableRow::getValues() const {
    return values;
}

bool TableRow::operator==(const TableRow& other) const {
    return values == other.values;
}

string TableRow::toString() const {
    ostringstream oss;
    for (auto it = values.begin(); it != values.end(); ++it) {
        if (it != values.begin()) {
            oss << " "; // Add space before all but the first entity's name
        }
        oss << (*it)->getName(); // Dereference the iterator and shared_ptr to call getName
    }
    return oss.str();
}
// ai-gen end