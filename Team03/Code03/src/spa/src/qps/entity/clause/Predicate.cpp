#include "Predicate.h"

bool Predicate::isValidRow(const vector<shared_ptr<Entity>>& row) const {
    if (row.size() != validators.size()) {
        throw QPSEvaluationException("Predicate: mismatch between row size and validator size, row size: "
        + to_string(row.size()) + ", validator size: " + to_string(validators.size()));
    }
    for (int i = 0; i < row.size(); i++) {
        if (!validators[i]->validate(row[i])) {
            return false;
        }
    }
    return true;
}

std::string Predicate::toString() const {
    return "Predicate";
}