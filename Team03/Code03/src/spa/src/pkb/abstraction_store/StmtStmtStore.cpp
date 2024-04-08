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

bool StmtStmtStore::add(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
    if (!checkValidity(stmt1, stmt2)) {
        return false;
    }
    directMap[stmt1].insert(stmt2);
    transitiveMap[stmt1].insert(stmt2);
    helperMap[stmt2] = stmt1;
    // iterate through all ancestor to craft the transitive map
    // assumes that whatever traversal of the program follows dfs order / is correct
    auto ancestor = stmt1;
    while (helperMap.find(ancestor) != helperMap.end()) {
        ancestor = helperMap[ancestor];
        transitiveMap[ancestor].insert(stmt2);
        // terminates once this ancestor is the "root"
    }
    return true;
}

bool StmtStmtStore::checkValidity(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
    return true;
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
    helperMap.clear();
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