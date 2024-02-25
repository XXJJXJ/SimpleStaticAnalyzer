#pragma once

#include <unordered_map>
#include <unordered_set>
#include "common/Statement.h"
#include "common/EntityType.h"
#include "common/Variable.h"

using namespace std;

// SPV is a statement/procedure to Variable store
class SPVStore {
private:
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> allStmts;
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> assignStmts;
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> printStmts;
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> readStmts;
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> ifWhileStmts;
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> callStmts;

    unordered_map<EntityType, vector<vector<shared_ptr<Entity>>>> cache;
    // string or procedure object?
    unordered_map<string, unordered_set<shared_ptr<Variable>>> procedureToVar;
    vector<vector<shared_ptr<Entity>>> getStmtVarPairs(const unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>>& table, EntityType type);
public:
    virtual bool add(shared_ptr<Statement> stmt, shared_ptr<Variable> var);

    virtual vector<vector<shared_ptr<Entity>>> getByAssign();
    virtual vector<vector<shared_ptr<Entity>>> getByPrint();
    virtual vector<vector<shared_ptr<Entity>>> getByRead();
    virtual vector<vector<shared_ptr<Entity>>> getByIfWhileStmt();
    virtual vector<vector<shared_ptr<Entity>>> getByCall();
    virtual vector<vector<shared_ptr<Entity>>> getByAllStmt();

    // For testing
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getAllMap();
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getReadMap();
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getPrintMap();
    unordered_map<string, unordered_set<shared_ptr<Variable>>> getByProcedureMap();
    virtual void clear();
    virtual ~SPVStore();
};