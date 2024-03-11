#include "BooleanTable.h"
#include "HeaderTable.h" // Include this if you need to specifically handle HeaderTable
#include <stdexcept> // For std::dynamic_pointer_cast

BooleanTable::BooleanTable(const BaseTable& table) : BaseTable() {
    // If the input table is not empty, store false; otherwise, store true
    this->value = !table.isEmpty();
}

std::shared_ptr<BaseTable> BooleanTable::join(BaseTable& other) {
    // Try to cast 'other' to BooleanTable
    auto otherBoolTable = dynamic_cast<BooleanTable*>(&other);
    if (otherBoolTable != nullptr) {
        // If 'other' is a BooleanTable, return a new BooleanTable based on the logical AND of both tables' values
        return std::make_shared<BooleanTable>(BaseTable()); // Placeholder, set the correct boolean value
    } else {
        // If 'other' is not a BooleanTable, check the value of the current BooleanTable
        if (this->value) {
            // If current table's value is true, return 'other' as it is
            return std::make_shared<BaseTable>(other);
        } else {
            // If current table's value is false, return an empty version of 'other'
            // Assuming 'other' can be cleared or recreated empty
            other.clearRows(); // Placeholder, assuming 'clear()' method exists or you can recreate 'other' as empty
            return std::make_shared<BaseTable>(other);
        }
    }
}

// A special logic for boolean table, false implies empty and true implies non-empty
bool BooleanTable::isEmpty() const {
    return !this->value;
}

bool BooleanTable::isTrue() const {
    return this->value;
}

bool BooleanTable::isBoolean() const {
    return true;
}

bool BooleanTable::operator==(const BaseTable &other) const {
    // Try to cast 'other' to BooleanTable
    auto otherBoolTable = dynamic_cast<const BooleanTable*>(&other);
    if (otherBoolTable != nullptr) {
        // If 'other' is a BooleanTable, compare the values of both tables
        return this->value == otherBoolTable->value;
    } else {
        // If 'other' is not a BooleanTable, return false
        return false;
    }
}

BooleanTable::BooleanTable(bool value) {
    this->value = value;
}

vector<string> BooleanTable::toStrings() {
    return {this->value ? "TRUE" : "FALSE"};
}
