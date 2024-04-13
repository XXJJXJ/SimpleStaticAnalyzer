#pragma once

#include <memory>

#include "common/expression/Constant.h"
#include "common/expression/Variable.h"
#include "../entity_store/ConstVarStore.h"
#include "../entity_store/ProcedureStore.h"
#include "../entity_store/StatementStore.h"


using namespace std;

class EntityManager {
private:
    // Private constructor to prevent external instantiation
    EntityManager() {}
    static shared_ptr<EntityManager> instance;

    ConstVarStore constantStore;
    ConstVarStore variableStore;
    ProcedureStore procStore;
    StatementStore stmtStore;

    void clearStore();
public:
    // Public method to get the instance of the class
    static shared_ptr<EntityManager> getInstance();

    bool addConstant(shared_ptr<Constant> c);
    vector<shared_ptr<Entity>> getAllConstants();

    bool addVariable(shared_ptr<Variable> var);
    vector<shared_ptr<Entity>> getAllVariables();
    shared_ptr<Entity> getVariableByName(string var);

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