#pragma once

#include <unordered_map>
#include <unordered_set>
#include "common/Statement.h"

using namespace std;

// Pure interface class
class StmtStmtStore {
protected:
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> directMap;
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> transitiveMap;

public:
    // helper function
    static vector<vector<shared_ptr<Entity>>> getStmtPairs(const unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>>& table);
    virtual bool add(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) = 0;
    virtual void clear() = 0;
    // using stmt - vector to accomodate parent
    vector<vector<shared_ptr<Entity>>> getDirect();
    virtual vector<vector<shared_ptr<Entity>>> getTransitive();
    virtual unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> getDirectMap();
    virtual unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> getTransitiveMap();
};