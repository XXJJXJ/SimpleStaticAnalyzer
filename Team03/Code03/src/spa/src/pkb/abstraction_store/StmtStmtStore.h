#pragma once

#include <unordered_map>
#include <unordered_set>
#include "common/statement/Statement.h"

using namespace std;

// Pure interface class
class StmtStmtStore {
protected:
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> directMap;
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> transitiveMap;
    unordered_map<shared_ptr<Statement>, shared_ptr<Statement>> helperMap;

    vector<vector<shared_ptr<Entity>>> directCache;
    vector<vector<shared_ptr<Entity>>> transitiveCache;
public:
    // helper function
    static vector<vector<shared_ptr<Entity>>> getStmtPairs(
        const unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> &table);
    virtual bool add(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2);
    virtual void clear();
    // using stmt - vector to accomodate parent
    virtual bool checkValidity(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2);
    vector<vector<shared_ptr<Entity>>> getDirect();
    virtual vector<vector<shared_ptr<Entity>>> getTransitive();
    virtual unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> getDirectMap();
    virtual unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> getTransitiveMap();
};