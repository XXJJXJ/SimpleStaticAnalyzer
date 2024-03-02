#pragma once

#include <unordered_map>
#include <unordered_set>
#include "common/Entity.h"

using namespace std;

// Pure interface class
class DirectTransitiveStore {
protected:
    unordered_map<shared_ptr<Entity>, unordered_set<shared_ptr<Entity>>> directMap;
    unordered_map<shared_ptr<Entity>, unordered_set<shared_ptr<Entity>>> transitiveMap;
public:
    virtual bool add(shared_ptr<Entity> ent1, shared_ptr<Entity> ent2) = 0;
    virtual void clear() = 0;
    // using stmt - vector to accomodate parent
    vector<vector<shared_ptr<Entity>>> getDirect();
    vector<vector<shared_ptr<Entity>>> getTransitive();
    unordered_map<shared_ptr<Entity>, unordered_set<shared_ptr<Entity>>> getDirectMap();
    unordered_map<shared_ptr<Entity>, unordered_set<shared_ptr<Entity>>> getTransitiveMap();
};