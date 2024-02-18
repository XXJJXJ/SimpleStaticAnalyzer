#include "WhileStatementStore.h"

WhileStatementStore::WhileStatementStore() : lineToWhileStatementMap() {}

bool WhileStatementStore::add(shared_ptr<WhileStatement> stmt) {
    if (lineToWhileStatementMap.find(stmt->getStatementNumber()) != lineToWhileStatementMap.end()) {
        return false;
    }
    lineToWhileStatementMap[stmt->getStatementNumber()] = stmt;
    return true;
}

vector<shared_ptr<WhileStatement>> WhileStatementStore::getAll() const {
    vector<shared_ptr<WhileStatement>> allStatements;
    for (const auto& item : lineToWhileStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}

void WhileStatementStore::clear() {
    lineToWhileStatementMap.clear();
}

WhileStatementStore::~WhileStatementStore() {
    clear();
}