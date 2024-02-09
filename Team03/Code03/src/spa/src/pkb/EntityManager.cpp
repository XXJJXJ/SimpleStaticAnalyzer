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

// Constants
// bool EntityManager::addConstant(shared_ptr<Constant> c) {
//     return constantStore.add(c);
// }

// vector<shared_ptr<Constant>> EntityManager::getAllConstants() {
//     return constantStore.getAll();
// }

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
    return printStore.add(printStmt);
}

vector<shared_ptr<PrintStatement>> EntityManager::getAllPrintStatements() {
    return printStore.getAll();
}

// Read Statements
bool EntityManager::addReadStatement(shared_ptr<ReadStatement> readStmt) {
    return readStore.add(readStmt);
}

vector<shared_ptr<ReadStatement>> EntityManager::getAllReadStatements() {
    return readStore.getAll();
}

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
}