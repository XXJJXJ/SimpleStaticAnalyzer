#pragma once

#include <string>

#include "common/Variable.h"
#include "entity_store/NormalStore.h"
#include "entity_store/ProcedureStore.h"
#include "entity_store/StatementStore.h"
#include "entity_store/PrintStatementStore.h"
#include "entity_store/ReadStatementStore.h"

using namespace std;

class EntityManager {
private:
    // Private constructor to prevent external instantiation
    EntityManager() {}
    static EntityManager* instance;

private:
    // NormalStore<Constant> constantStore;
    NormalStore<Variable> variableStore;
    ProcedureStore procStore;
    // Statement stores
    StatementStore allStmtStore;
    PrintStatementStore printStore;
    ReadStatementStore readStore;
private:
    void clearStore();
public:
    // Public method to get the instance of the class
    static EntityManager* getInstance();

    // bool addConstant(shared_ptr<Constant> c);
    // vector<shared_ptr<Constant>> getAllConstants();

    bool addVariable(shared_ptr<Variable> var);
    vector<shared_ptr<Variable>> getAllVariables();

    bool addProcedure(shared_ptr<Procedure> proc);
    vector<shared_ptr<Procedure>> getAllProcedures();

    bool addPrintStatement(shared_ptr<PrintStatement> printStmt);
    vector<shared_ptr<PrintStatement>> getAllPrintStatements();

    bool addReadStatement(shared_ptr<ReadStatement> readStmt);
    vector<shared_ptr<ReadStatement>> getAllReadStatements();

    vector<shared_ptr<Statement>> getAllStatements();

    static void clear();
    ~EntityManager();
};