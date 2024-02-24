#pragma once

#include <memory>

#include "common/Constant.h"
#include "common/Variable.h"
#include "entity_store/NormalStore.h"
#include "entity_store/ProcedureStore.h"
#include "entity_store/StatementStore.h"
#include "entity_store/AssignStatementStore.h"
#include "entity_store/PrintStatementStore.h"
#include "entity_store/ReadStatementStore.h"
#include "entity_store/IfStatementStore.h"
#include "entity_store/WhileStatementStore.h"

// Temp include to remove after implementation of stores
#include "common/CallStatement.h"
// End of Temp include


using namespace std;

class EntityManager {
private:
    // Private constructor to prevent external instantiation
    EntityManager() {}
    static shared_ptr<EntityManager> instance;

    NormalStore<Constant> constantStore;
    NormalStore<Variable> variableStore;
    ProcedureStore procStore;
    // Statement stores
    StatementStore allStmtStore;
    AssignStatementStore assignStore;
    PrintStatementStore printStore;
    ReadStatementStore readStore;
    IfStatementStore ifStore;
    WhileStatementStore whileStore;

    void clearStore();
public:
    // Public method to get the instance of the class
    static shared_ptr<EntityManager> getInstance();

    bool addConstant(shared_ptr<Constant> c);
    vector<shared_ptr<Constant>> getAllConstants();

    bool addVariable(shared_ptr<Variable> var);
    vector<shared_ptr<Variable>> getAllVariables();

    bool addProcedure(shared_ptr<Procedure> proc);
    vector<shared_ptr<Procedure>> getAllProcedures();

    bool addPrintStatement(shared_ptr<PrintStatement> printStmt);
    vector<shared_ptr<PrintStatement>> getAllPrintStatements();

    bool addReadStatement(shared_ptr<ReadStatement> readStmt);
    vector<shared_ptr<ReadStatement>> getAllReadStatements();

    bool addAssignStatement(shared_ptr<AssignStatement> assignStmt);
    vector<shared_ptr<AssignStatement>> getAllAssignStatements();

    bool addIfStatement(shared_ptr<IfStatement> ifStmt);
    vector<shared_ptr<IfStatement>> getAllIfStatements();

    bool addWhileStatement(shared_ptr<WhileStatement> whileStmt);
    vector<shared_ptr<WhileStatement>> getAllWhileStatements();

    bool addCallStatement(shared_ptr<CallStatement> callStmt);
    vector<shared_ptr<CallStatement>> getAllCallStatements();

    vector<shared_ptr<Statement>> getAllStatements();

    shared_ptr<Procedure> getProcByName(const string& procName);

    static void clear();
    ~EntityManager();
};