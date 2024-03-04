#include "CallStore.h"

bool CallStore::add(shared_ptr<Entity> caller, shared_ptr<Entity> callee) {
    // Can't detect cycles here anyways
    directMap[caller].insert(callee);
    // Calculate transitive at the very end
    // transitiveMap[caller].insert(callee);
    return true;
}

unordered_set<shared_ptr<Entity>> visited;
void CallStore::tabulate() {
    // Prep for DFS
    unordered_set<shared_ptr<Entity>> called;
    unordered_set<shared_ptr<Entity>> roots;
    for (auto & _pair : directMap) {
        for (auto & proc : _pair.second) {
            called.insert(proc);
            // if a root is now called, remove
            if (roots.find(proc) != roots.end()) {
                roots.erase(proc);
            }
        }
        // Only insert the node if not inside called
        if (called.find(_pair.first) == called.end()) {
            roots.insert(_pair.first);
        }
    }
    // Start DFS from the roots - returns a vector of shared_ptr<Procedures> to be added to the set
    // And memoize
    // in a post order way
    if (roots.size() == 0 && called.size() > 0) {
        throw SemanticErrorException("Call cycles detected: No main procedure");
    }
    for (auto & r : roots) {
        // Should be guaranteed to be not within visited (due to above prep chunk)
        dfsAdd(r);
    }
    visited.clear();
}

// Transitive map used as memoized map
unordered_set<shared_ptr<Entity>> CallStore::dfsAdd(shared_ptr<Entity> proc) {
    if (transitiveMap.find(proc) != transitiveMap.end()) {
        return transitiveMap[proc];
    }
    if (visited.find(proc) != visited.end()) {
        // cycle detected
        throw SemanticErrorException("Procedures have call cycles");
    }
    visited.insert(proc);
    unordered_set<shared_ptr<Entity>> res;
    if (directMap.find(proc) != directMap.end()) {
        auto calledByThis = directMap[proc];
        for (auto & c : calledByThis) {
            auto cRes = dfsAdd(c);
            res.insert(cRes.begin(), cRes.end());
        }
    }
    // If empty, then just add self can alr
    res.insert(proc);
    transitiveMap[proc] = res; // memoize
    return res;
}

void CallStore::clear() {
    directMap.clear();
    transitiveMap.clear();
}

CallStore::~CallStore() {
    clear();
}
