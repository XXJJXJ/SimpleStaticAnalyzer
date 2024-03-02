#include "DirectTransitiveStore.h"


vector<vector<shared_ptr<Entity>>> getStmtPairs(const unordered_map<shared_ptr<Entity>, unordered_set<shared_ptr<Entity>>>& table) {
    vector<vector<shared_ptr<Entity>>> res;
    for (auto &v : table) {
        auto stmt1 = v.first;
        for (auto stmt2 : v.second) {
            res.push_back({stmt1, stmt2});
        }
    }
    return res;
}

vector<vector<shared_ptr<Entity>>> DirectTransitiveStore::getDirect() {
    return getStmtPairs(directMap);
}
vector<vector<shared_ptr<Entity>>> DirectTransitiveStore::getTransitive() {
    return getStmtPairs(transitiveMap);
}

// For testing
unordered_map<shared_ptr<Entity>, unordered_set<shared_ptr<Entity>>> DirectTransitiveStore::getDirectMap() {
    return directMap;
}
unordered_map<shared_ptr<Entity>, unordered_set<shared_ptr<Entity>>> DirectTransitiveStore::getTransitiveMap() {
    return transitiveMap;
}