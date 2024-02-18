#include "IfStatementStore.h"

IfStatementStore::IfStatementStore() : lineToIfStatementMap() {}

bool IfStatementStore::add(shared_ptr<IfStatement> stmt) {
    if (lineToIfStatementMap.find(stmt->getStatementNumber()) != lineToIfStatementMap.end()) {
        return false;
    }
    lineToIfStatementMap[stmt->getStatementNumber()] = stmt;
    return true;
}

vector<shared_ptr<IfStatement>> IfStatementStore::getAll() const {
    vector<shared_ptr<IfStatement>> allStatements;
    for (const auto& item : lineToIfStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}

void IfStatementStore::clear() {
    lineToIfStatementMap.clear();
}

IfStatementStore::~IfStatementStore() {
    clear();
}