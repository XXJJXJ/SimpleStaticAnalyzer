#include "StatementStore.h"

StatementStore::StatementStore() : lineToStatementMap() {}

bool StatementStore::add(shared_ptr<Statement> stmt) {
    if (lineToStatementMap.find(stmt->getStatementNumber()) != lineToStatementMap.end()) {
        return false;
    }
    lineToStatementMap[stmt->getStatementNumber()] = stmt;
    return true;
}
vector<shared_ptr<Statement>> StatementStore::getAll() const {
    vector<shared_ptr<Statement>> allStatements;
    for (const auto& item : lineToStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}
void StatementStore::clear() {
    lineToStatementMap.clear();
}

StatementStore::~StatementStore() {
    clear();
}