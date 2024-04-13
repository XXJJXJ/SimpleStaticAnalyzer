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

vector<shared_ptr<Entity>> EntityManager::getAllVariables() {
    return variableStore.getAll();
}

shared_ptr<Entity> EntityManager::getVariableByName(string var) {
    return variableStore.get(var);
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
    return stmtStore.addPrint(printStmt);
}

vector<shared_ptr<PrintStatement>> EntityManager::getAllPrintStatements() {
    return stmtStore.getAllPrint();
}

// Read Statements
bool EntityManager::addReadStatement(shared_ptr<ReadStatement> readStmt) {
    return stmtStore.addRead(readStmt);
}

vector<shared_ptr<ReadStatement>> EntityManager::getAllReadStatements() {
    return stmtStore.getAllRead();
}

vector<shared_ptr<Statement>> EntityManager::getAllStatements() {
    return stmtStore.getAll();
}

// Constants
bool EntityManager::addConstant(shared_ptr<Constant> c) {
    return constantStore.add(c);
}

vector<shared_ptr<Entity>> EntityManager::getAllConstants() {
    return constantStore.getAll();
}

// Assign statements
bool EntityManager::addAssignStatement(shared_ptr<AssignStatement> assignStmt) {
    return stmtStore.addAssign(assignStmt);
}

vector<shared_ptr<AssignStatement>> EntityManager::getAllAssignStatements() {
    return stmtStore.getAllAssign();
}

// If
bool EntityManager::addIfStatement(shared_ptr<IfStatement> ifStmt) {
    return stmtStore.addIf(ifStmt);
}
vector<shared_ptr<IfStatement>> EntityManager::getAllIfStatements() {
    return stmtStore.getAllIf();
}

// While 
bool EntityManager::addWhileStatement(shared_ptr<WhileStatement> whileStmt) {
    return stmtStore.addWhile(whileStmt);
}
vector<shared_ptr<WhileStatement>> EntityManager::getAllWhileStatements() {
    return stmtStore.getAllWhile();
}


// Call
bool EntityManager::addCallStatement(shared_ptr<CallStatement> callStmt) {
    return stmtStore.addCall(callStmt);
}
vector<shared_ptr<CallStatement>> EntityManager::getAllCallStatements() {
    return stmtStore.getAllCall();
}

shared_ptr<Procedure> EntityManager::getProcByName(const string& procName) {
    return procStore.get(procName);
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
    stmtStore.clear();
}