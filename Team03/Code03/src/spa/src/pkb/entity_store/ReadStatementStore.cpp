#include "ReadStatementStore.h"

ReadStatementStore::ReadStatementStore() : lineToReadStatementMap() {}

bool ReadStatementStore::add(shared_ptr<ReadStatement> stmt) {
    if (lineToReadStatementMap.find(stmt->getStatementNumber()) != lineToReadStatementMap.end()) {
        return false;
    }
    lineToReadStatementMap[stmt->getStatementNumber()] = stmt;
    return true;
}
vector<shared_ptr<ReadStatement>> ReadStatementStore::getAll() const {
    vector<shared_ptr<ReadStatement>> allStatements;
    for (const auto& item : lineToReadStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}
void ReadStatementStore::clear() {
    lineToReadStatementMap.clear();
}

ReadStatementStore::~ReadStatementStore() {
    clear();
}