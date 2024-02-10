#include <vector>

#include "EntityManager.h"

// Initialize the static instance to nullptr
EntityManager* EntityManager::instance = nullptr;

// Implementation of EntityManager methods
EntityManager* EntityManager::getInstance() {
    if (!instance) {
        instance = new EntityManager();
    }
    return instance;
}


EntityManager::~EntityManager() {
    delete instance;
}

// Variables
bool EntityManager::addVariable(shared_ptr<Variable> var) {
    return variableStore.add(var);
}

vector<shared_ptr<Variable>> EntityManager::getAllVariables() {
    return variableStore.getAll();
}

// Procedures
bool EntityManager::addProcedure(shared_ptr<Procedure> proc) {
    return procStore.add(proc);
}

vector<shared_ptr<Procedure>> EntityManager::getAllProcedures() {
    return procStore.getAll();
}

// Print Statements
bool EntityManager::addPrintStatement(shared_ptr<PrintStatement> printStmt) {
    if (allStmtStore.add(printStmt)) {
        return printStore.add(printStmt);
    }
    return false;
}

vector<shared_ptr<PrintStatement>> EntityManager::getAllPrintStatements() {
    return printStore.getAll();
}

// Read Statements
bool EntityManager::addReadStatement(shared_ptr<ReadStatement> readStmt) {
    if (allStmtStore.add(readStmt)) {
        return readStore.add(readStmt);
    }
    return false;
}

vector<shared_ptr<ReadStatement>> EntityManager::getAllReadStatements() {
    return readStore.getAll();
}

vector<shared_ptr<Statement>> EntityManager::getAllStatements() {
    return allStmtStore.getAll();
}

// Constants
// bool EntityManager::addConstant(shared_ptr<Constant> c) {
//     return constantStore.add(c);
// }

// vector<shared_ptr<Constant>> EntityManager::getAllConstants() {
//     return constantStore.getAll();
// }


void EntityManager::clear() {
    if (!instance) {
        return;
    }
    instance->clearStore();
}

void EntityManager::clearStore() {
    // constantStore.clear();
    variableStore.clear();
    procStore.clear();
    allStmtStore.clear();
    readStore.clear();
    printStore.clear();
}