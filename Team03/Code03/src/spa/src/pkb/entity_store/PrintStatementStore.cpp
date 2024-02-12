#include "PrintStatementStore.h"

PrintStatementStore::PrintStatementStore() : lineToPrintStatementMap() {}

bool PrintStatementStore::add(shared_ptr<PrintStatement> stmt) {
    if (lineToPrintStatementMap.find(stmt->getStatementNumber()) != lineToPrintStatementMap.end()) {
        return false;
    }
    lineToPrintStatementMap[stmt->getStatementNumber()] = stmt;
    return true;
}
vector<shared_ptr<PrintStatement>> PrintStatementStore::getAll() const {
    vector<shared_ptr<PrintStatement>> allStatements;
    for (const auto& item : lineToPrintStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}
void PrintStatementStore::clear() {
    lineToPrintStatementMap.clear();
}

PrintStatementStore::~PrintStatementStore() {
    clear();
}