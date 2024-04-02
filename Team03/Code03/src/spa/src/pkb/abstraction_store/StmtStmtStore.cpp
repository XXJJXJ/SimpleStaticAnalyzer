#include "StmtStmtStore.h"


vector<vector<shared_ptr<Entity>>> StmtStmtStore::getStmtPairs(const unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>>& table) {
    vector<vector<shared_ptr<Entity>>> res;
    for (auto &v : table) {
        auto stmt1 = v.first;
        for (auto &stmt2 : v.second) {
            res.push_back({stmt1, stmt2});
        }
    }
    return res;
}

vector<vector<shared_ptr<Entity>>> StmtStmtStore::getDirect() {
    if (directCache.size() == 0) {
        directCache = getStmtPairs(directMap);
    }
    return directCache;
}
vector<vector<shared_ptr<Entity>>> StmtStmtStore::getTransitive() {
    if (transitiveCache.size() == 0) {
        transitiveCache = getStmtPairs(transitiveMap);
    }
    return transitiveCache;
}

void StmtStmtStore::clear() {
    directMap.clear();
    transitiveMap.clear();
    directCache.clear();
    transitiveCache.clear();
}

// For testing
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> StmtStmtStore::getDirectMap() {
    return directMap;
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> StmtStmtStore::getTransitiveMap() {
    return transitiveMap;
}