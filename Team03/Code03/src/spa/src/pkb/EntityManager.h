#pragma once


#include <iostream>
#include <string>
#include <set>
#include "common/Entity.h"
#include "Store.h"
#include "StatementStore.h"

using namespace std;
class EntityManager {
private:
    // Private constructor to prevent external instantiation
    EntityManager() {}
    // Private static instance of the class
    static EntityManager* instance;

private:
    // NormalStore<Constant> constantStore;
    NormalStore<Variable> variableStore;
    ProcedureStore procStore;
    // Statement stores
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

    static void clear();
    ~EntityManager();
};