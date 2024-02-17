#include <vector>

#include "EntityManager.h"

// Initialize the static instance to nullptr
shared_ptr<EntityManager> EntityManager::instance = nullptr;

// Implementation of EntityManager methods
shared_ptr<EntityManager> EntityManager::getInstance() {
    if (!instance) {
        EntityManager* em = new EntityManager();
        instance = make_shared<EntityManager>(*em);
    }
    return instance;
}


EntityManager::~EntityManager() {}

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
bool EntityManager::addConstant(shared_ptr<Constant> c) {
    return constantStore.add(c);
}

vector<shared_ptr<Constant>> EntityManager::getAllConstants() {
    return constantStore.getAll();
}

// Assign statements
bool EntityManager::addAssignStatement(shared_ptr<AssignStatement> assignStmt) {
    if (allStmtStore.add(assignStmt)) {
        return assignStore.add(assignStmt);
    }
    return false;
}

vector<shared_ptr<AssignStatement>> EntityManager::getAllAssignStatements() {
    return assignStore.getAll();
}

// If
bool EntityManager::addIfStatement(shared_ptr<IfStatement> ifStmt) {
    if (allStmtStore.add(ifStmt)) {
        return ifStore.add(ifStmt);
    }
    return false;
}
vector<shared_ptr<IfStatement>> EntityManager::getAllIfStatements() {
    return ifStore.getAll();
}

// While 
bool EntityManager::addWhileStatement(shared_ptr<WhileStatement> whileStmt) {
    if (allStmtStore.add(whileStmt)) {
        return whileStore.add(whileStmt);
    }
    return false;
}
vector<shared_ptr<WhileStatement>> EntityManager::getAllWhileStatements() {
    return whileStore.getAll();
}


// Call
bool EntityManager::addCallStatement(shared_ptr<CallStatement> callStmt) {
    if (allStmtStore.add(callStmt)) {
        return true;
    }
    return false;
}
vector<shared_ptr<CallStatement>> EntityManager::getAllCallStatements() {
    return {};
}


void EntityManager::clear() {
    if (!instance) {
        return;
    }
    instance->clearStore();
}

void EntityManager::clearStore() {
    constantStore.clear();
    variableStore.clear();
    procStore.clear();

    allStmtStore.clear();
    readStore.clear();
    printStore.clear();
    assignStore.clear();
    ifStore.clear();
    whileStore.clear();
}