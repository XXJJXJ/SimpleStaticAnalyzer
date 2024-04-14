#include "StatementStore.h"

StatementStore::StatementStore() : lineToStatementMap() {}

bool StatementStore::add(shared_ptr<Statement> stmt) {
    if (lineToStatementMap.find(stmt->getStatementNumber()) != lineToStatementMap.end()) {
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

vector<shared_ptr<Statement>> StatementStore::getAll() {
    if (allStatementsCache.size() == 0) {
        for (const auto &item : lineToStatementMap) {
            allStatementsCache.push_back(item.second);
        }
        lineToStatementMap.clear(); // reduce memory usage
    }
    return allStatementsCache;
}

vector<shared_ptr<AssignStatement>> StatementStore::getAllAssign() {
    if (assignStatementsCache.size() == 0) {
        for (const auto &item : lineToAssignStatementMap) {
            assignStatementsCache.push_back(item.second);
        }
        lineToAssignStatementMap.clear();
    }
    return assignStatementsCache;
}

vector<shared_ptr<CallStatement>> StatementStore::getAllCall() {
    if (callStatementsCache.size() == 0) {
        for (const auto &item : lineToCallStatementMap) {
            callStatementsCache.push_back(item.second);
        }
        lineToCallStatementMap.clear();
    }
    return callStatementsCache;
}

vector<shared_ptr<IfStatement>> StatementStore::getAllIf() {
    if (ifStatementsCache.size() == 0) {
        for (const auto &item : lineToIfStatementMap) {
            ifStatementsCache.push_back(item.second);
        }
        lineToIfStatementMap.clear();
    }
    return ifStatementsCache;
}

vector<shared_ptr<PrintStatement>> StatementStore::getAllPrint() {
    if (printStatementsCache.size() == 0) {
        for (const auto &item : lineToPrintStatementMap) {
            printStatementsCache.push_back(item.second);
        }
        lineToPrintStatementMap.clear();
    }
    return printStatementsCache;
}

vector<shared_ptr<ReadStatement>> StatementStore::getAllRead() {
    if (readStatementsCache.size() == 0) {
        for (const auto &item : lineToReadStatementMap) {
            readStatementsCache.push_back(item.second);
        }
        lineToReadStatementMap.clear();
    }
    return readStatementsCache;
}

vector<shared_ptr<WhileStatement>> StatementStore::getAllWhile() {
    if (whileStatementsCache.size() == 0) {
        for (const auto &item : lineToWhileStatementMap) {
            whileStatementsCache.push_back(item.second);
        }
        lineToWhileStatementMap.clear();
    }
    return whileStatementsCache;
}

void StatementStore::clear() {
    lineToStatementMap.clear();
    lineToAssignStatementMap.clear();
    lineToCallStatementMap.clear();
    lineToPrintStatementMap.clear();
    lineToIfStatementMap.clear();
    lineToReadStatementMap.clear();
    lineToWhileStatementMap.clear();

    allStatementsCache.clear();
    assignStatementsCache.clear();
    callStatementsCache.clear();
    readStatementsCache.clear();
    printStatementsCache.clear();
    whileStatementsCache.clear();
    ifStatementsCache.clear();
}

StatementStore::~StatementStore() {
    clear();
}