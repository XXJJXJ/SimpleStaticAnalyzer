#include "StatementStore.h"

StatementStore::StatementStore() : lineToStatementMap() {}

bool StatementStore::checkStmt(shared_ptr<Statement> stmt) {
    return lineToStatementMap.find(stmt->getStatementNumber()) != lineToStatementMap.end();
}

bool StatementStore::add(shared_ptr<Statement> stmt) {
    if (checkStmt(stmt)) {
        return false;
    }
    lineToStatementMap[stmt->getStatementNumber()] = stmt;
    return true;
}

bool StatementStore::addAssign(shared_ptr<AssignStatement> stmt) {
    if (add(stmt)) {
        lineToAssignStatementMap[stmt->getStatementNumber()] = stmt;
        return true;
    }
    return false;
}

bool StatementStore::addCall(shared_ptr<CallStatement> stmt) {
    if (add(stmt)) {
        lineToCallStatementMap[stmt->getStatementNumber()] = stmt;
        return true;
    }
    return false;
}

bool StatementStore::addIf(shared_ptr<IfStatement> stmt) {
    if (add(stmt)) {
        lineToIfStatementMap[stmt->getStatementNumber()] = stmt;
        return true;
    }
    return false;
}

bool StatementStore::addRead(shared_ptr<ReadStatement> stmt) {
    if (add(stmt)) {
        lineToReadStatementMap[stmt->getStatementNumber()] = stmt;
        return true;
    }
    return false;
}

bool StatementStore::addPrint(shared_ptr<PrintStatement> stmt) {
    if (add(stmt)) {
        lineToPrintStatementMap[stmt->getStatementNumber()] = stmt;
        return true;
    }
    return false;
}

bool StatementStore::addWhile(shared_ptr<WhileStatement> stmt) {
    if (add(stmt)) {
        lineToWhileStatementMap[stmt->getStatementNumber()] = stmt;
        return true;
    }
    return false;
}

vector<shared_ptr<Statement>> StatementStore::getAll() const {
    vector<shared_ptr<Statement>> allStatements;
    for (const auto& item : lineToStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}

vector<shared_ptr<AssignStatement>> StatementStore::getAllAssign() const {
    vector<shared_ptr<AssignStatement>> allStatements;
    for (const auto& item : lineToAssignStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}

vector<shared_ptr<CallStatement>> StatementStore::getAllCall() const {
    vector<shared_ptr<CallStatement>> allStatements;
    for (const auto& item : lineToCallStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}

vector<shared_ptr<IfStatement>> StatementStore::getAllIf() const {
    vector<shared_ptr<IfStatement>> allStatements;
    for (const auto& item : lineToIfStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}

vector<shared_ptr<PrintStatement>> StatementStore::getAllPrint() const {
    vector<shared_ptr<PrintStatement>> allStatements;
    for (const auto& item : lineToPrintStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}

vector<shared_ptr<ReadStatement>> StatementStore::getAllRead() const {
    vector<shared_ptr<ReadStatement>> allStatements;
    for (const auto& item : lineToReadStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}

vector<shared_ptr<WhileStatement>> StatementStore::getAllWhile() const {
    vector<shared_ptr<WhileStatement>> allStatements;
    for (const auto& item : lineToWhileStatementMap) {
        allStatements.push_back(item.second);
    }
    return allStatements;
}

void StatementStore::clear() {
    lineToStatementMap.clear();
    lineToAssignStatementMap.clear();
    lineToCallStatementMap.clear();
    lineToPrintStatementMap.clear();
    lineToIfStatementMap.clear();
    lineToReadStatementMap.clear();
    lineToWhileStatementMap.clear();
}

StatementStore::~StatementStore() {
    clear();
}