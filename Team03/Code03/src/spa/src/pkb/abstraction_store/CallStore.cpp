#include "CallStore.h"

bool CallStore::add(shared_ptr<Procedure> caller, shared_ptr<Procedure> callee) {
    // Can't detect cycles here anyways
    directMap[caller].insert(callee);
    // Calculate transitive at the very end
    return true;
}


void CallStore::tabulate() {
    // Prep for DFS
    unordered_set<shared_ptr<Procedure>> nonRoots;
    unordered_set<shared_ptr<Procedure>> roots;
    for (auto & _pair : directMap) {
        for (auto & callee : _pair.second) {
            nonRoots.insert(callee);
            // if a root is now called, remove
            if (roots.find(callee) != roots.end()) {
                roots.erase(callee);
            }
        }
        // Only insert the node if not inside called
        if (nonRoots.find(_pair.first) == nonRoots.end()) {
            roots.insert(_pair.first);
        }
    }
    // Start DFS from the roots - returns a vector of shared_ptr<Procedures> to be added to the set
    // And memoize
    // in a post order way
    if (roots.size() == 0 && nonRoots.size() > 0) {
        throw SemanticErrorException("Call cycles detected: No main procedure");
    }
    // Cannot use entity here since comparator for entity not establish
    unordered_set<shared_ptr<Procedure>> visited;
    for (auto & r : roots) {
        // Should be guaranteed to be not within visited (due to above prep chunk)
        dfsAdd(r, visited);
    }
    visited.clear();
}

// Transitive map used as memoized map
unordered_set<shared_ptr<Procedure>> CallStore::dfsAdd(shared_ptr<Procedure> proc, unordered_set<shared_ptr<Procedure>>& visited) {
    if (transitiveMap.find(proc) != transitiveMap.end()) {
        return transitiveMap[proc];
    }
    if (visited.find(proc) != visited.end()) {
        throw SemanticErrorException("Procedures have call cycles");
    }
    visited.insert(proc);
    unordered_set<shared_ptr<Procedure>> res;
    if (directMap.find(proc) != directMap.end()) {
        auto calledByThis = directMap[proc];
        for (auto & c : calledByThis) {
            auto cRes = dfsAdd(c, visited);
            res.insert(cRes.begin(), cRes.end());
        }
    }
    // If empty, then just add self can alr
    res.insert(proc);
    transitiveMap[proc] = res; // memoize
    return res;
}


vector<vector<shared_ptr<Entity>>> getProcPairs(const unordered_map<shared_ptr<Procedure>, unordered_set<shared_ptr<Procedure>>>& table) {
    vector<vector<shared_ptr<Entity>>> res;
    for (auto &v : table) {
        auto stmt1 = v.first;
        for (auto &stmt2 : v.second) {
            res.push_back({stmt1, stmt2});
        }
    }
    return res;
}

vector<vector<shared_ptr<Entity>>> CallStore::getDirect() {
    return getProcPairs(directMap);
}
vector<vector<shared_ptr<Entity>>> CallStore::getTransitive() {
    return getProcPairs(transitiveMap);
}

unordered_map<shared_ptr<Procedure>, unordered_set<shared_ptr<Procedure>>> CallStore::getTransitiveMap() {
    return transitiveMap;
}

void CallStore::clear() {
    directMap.clear();
    transitiveMap.clear();
}

CallStore::~CallStore() {
    clear();
}
