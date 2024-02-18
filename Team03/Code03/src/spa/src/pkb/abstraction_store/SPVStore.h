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
    // string or procedure object?
    unordered_map<string, set<shared_ptr<Variable>>> procedureToVar;
public:
    virtual bool add(shared_ptr<Statement> stmt, shared_ptr<Variable> var);

    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getByAssign();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getByPrint();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getByRead();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getByIfWhileStmt();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getByCall();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getByAllStmt();
    virtual unordered_map<string, set<shared_ptr<Variable>>> getByProcedure();
    virtual void clear();
    virtual ~SPVStore();
};