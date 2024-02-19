#include "AssignStatementStore.h"

AssignStatementStore::AssignStatementStore() : lineToAssignStatementMap() {}

bool AssignStatementStore::add(shared_ptr<AssignStatement> stmt) {
    if (lineToAssignStatementMap.find(stmt->getStatementNumber()) != lineToAssignStatementMap.end()) {
        return false;
    }
    lineToAssignStatementMap[stmt->getStatementNumber()] = stmt;
    return true;
}

vector<shared_ptr<AssignStatement>> AssignStatementStore::getAll() const {
    vector<shared_ptr<AssignStatement>> allStatements;
    for (const auto& item : lineToAssignStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}

void AssignStatementStore::clear() {
    lineToAssignStatementMap.clear();
}

AssignStatementStore::~AssignStatementStore() {
    clear();
}