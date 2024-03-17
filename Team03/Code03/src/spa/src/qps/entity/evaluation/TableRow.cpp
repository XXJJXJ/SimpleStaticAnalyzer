// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
// prompt: https://chat.openai.com/share/eadbc02c-9e25-4f11-b2bb-c215c525d944

#include "TableRow.h"


// Implementation of TableRow
TableRow::TableRow(const vector<shared_ptr<Entity>> &values) : values(values) {}

const vector<shared_ptr<Entity>> &TableRow::getValues() const {
    return values;
}

bool TableRow::operator==(const TableRow &other) const {
    if (values.size() != other.values.size()) {
        return false;
    }
    for (size_t i = 0; i < values.size(); ++i) {
        if (values[i]->getName() != other.values[i]->getName() ||
            values[i]->getType() != other.values[i]->getType()) {
            return false;
        }
    }
    return true;
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

std::shared_ptr<Entity> TableRow::getByIndex(int index) const {
    if (index >= 0 && index < values.size()) {
        return values[index];
    }
    throw std::out_of_range("Index out of range in TableRow::getByIndex");
}

bool TableRow::operator<(const TableRow& other) const {
    const auto& valuesA = getValues();
    const auto& valuesB = other.getValues();
    if (valuesA.size() != valuesB.size()) {
        return valuesA.size() < valuesB.size();
    }
    for (size_t i = 0; i < valuesA.size(); ++i) {
        if (*valuesA[i] != *valuesB[i]) { // First, check for equality
            return *valuesA[i] < *valuesB[i]; // Then determine order
        }
    }
    return false; // Rows are equal
}