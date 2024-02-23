#pragma once

#include <set>
#include <unordered_map>
#include "common/Statement.h"
#include "common/EntityType.h"
#include "common/Variable.h"

using namespace std;

// SPV is a statement/procedure to Variable store
class SPVStore {
private:
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> allStmts;
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> assignStmts;
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> printStmts;
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> readStmts;
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> ifWhileStmts;
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> callStmts;

    unordered_map<EntityType, vector<vector<shared_ptr<Entity>>>> cache;
    // string or procedure object?
    unordered_map<string, set<shared_ptr<Variable>>> procedureToVar;
    vector<vector<shared_ptr<Entity>>> getStmtVarPairs(const unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>>& table, EntityType type);
public:
    virtual bool add(shared_ptr<Statement> stmt, shared_ptr<Variable> var);

    virtual vector<vector<shared_ptr<Entity>>> getByAssign();
    virtual vector<vector<shared_ptr<Entity>>> getByPrint();
    virtual vector<vector<shared_ptr<Entity>>> getByRead();
    virtual vector<vector<shared_ptr<Entity>>> getByIfWhileStmt();
    virtual vector<vector<shared_ptr<Entity>>> getByCall();
    virtual vector<vector<shared_ptr<Entity>>> getByAllStmt();
    virtual unordered_map<string, set<shared_ptr<Variable>>> getByProcedure();

    // For testing
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getAllMap();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getReadMap();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getPrintMap();
    virtual void clear();
    virtual ~SPVStore();
};