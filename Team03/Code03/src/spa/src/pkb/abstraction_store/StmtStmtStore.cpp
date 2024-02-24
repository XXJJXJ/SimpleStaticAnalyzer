#include "StmtStmtStore.h"


vector<vector<shared_ptr<Entity>>> getStmtPairs(const unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>>& table) {
    vector<vector<shared_ptr<Entity>>> res;
    for (auto &v : table) {
        auto stmt1 = v.first;
        for (auto stmt2 : v.second) {
            res.push_back({stmt1, stmt2});
        }
    }
    return res;
}

vector<vector<shared_ptr<Entity>>> StmtStmtStore::getDirect() {
    return getStmtPairs(directMap);
}
vector<vector<shared_ptr<Entity>>> StmtStmtStore::getTransitive() {
    return getStmtPairs(transitiveMap);
}

// For testing
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> StmtStmtStore::getDirectMap() {
    return directMap;
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> StmtStmtStore::getTransitiveMap() {
    return transitiveMap;
}