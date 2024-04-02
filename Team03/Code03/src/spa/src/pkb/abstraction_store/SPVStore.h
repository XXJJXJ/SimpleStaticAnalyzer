#pragma once

#include <unordered_map>
#include <unordered_set>
#include "common/statement/Statement.h"
#include "common/EntityType.h"
#include "common/expression/Variable.h"
#include "common/Procedure.h"

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
    vector<vector<shared_ptr<Entity>>> procVarCache;
    // string or procedure object?
    unordered_map<string, unordered_set<shared_ptr<Variable>>> procedureToVar;
    vector<vector<shared_ptr<Entity>>> getStmtVarPairs(const unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>>& table, EntityType type);
    vector<vector<shared_ptr<Entity>>> getProcVarPairs(unordered_map<string, unordered_set<shared_ptr<Variable>>> map);
public:
    virtual bool add(shared_ptr<Statement> stmt, shared_ptr<Variable> var);

    virtual vector<vector<shared_ptr<Entity>>> getByType(EntityType entType);
    virtual unordered_map<string, unordered_set<shared_ptr<Variable>>> getByProcedureMap();

    // For testing
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getAllMap();
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getReadMap();
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getPrintMap();
    
    virtual void clear();
    virtual ~SPVStore();
};