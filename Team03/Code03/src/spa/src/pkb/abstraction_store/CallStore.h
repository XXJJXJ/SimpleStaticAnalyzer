#pragma once

#include <unordered_map>
#include <unordered_set>
#include "common/Entity.h"
#include "common/Procedure.h"
#include "common/spa_exception/SemanticErrorException.h"

using namespace std;
// Notes: A procedure may be called by multiple procedures
// Itself can also call multiple procedures
class CallStore {
private:
    unordered_map<shared_ptr<Procedure>, unordered_set<shared_ptr<Procedure>>> directMap;
    unordered_map<shared_ptr<Procedure>, unordered_set<shared_ptr<Procedure>>> transitiveMap;

    vector<vector<shared_ptr<Entity>>> directRes;
    vector<vector<shared_ptr<Entity>>> transitiveRes;
    // Private helper
    unordered_set<shared_ptr<Procedure>> dfsAdd(
        shared_ptr<Procedure> proc, unordered_set<shared_ptr<Procedure>> &visited);
public:
    bool add(shared_ptr<Procedure> caller, shared_ptr<Procedure> callee);
    vector<vector<shared_ptr<Entity>>> getDirect();
    vector<vector<shared_ptr<Entity>>> getTransitive();
    void clear();
    void tabulate();
    ~CallStore();
    // Used internall
    unordered_map<shared_ptr<Procedure>, unordered_set<shared_ptr<Procedure>>> getTransitiveMap();
};