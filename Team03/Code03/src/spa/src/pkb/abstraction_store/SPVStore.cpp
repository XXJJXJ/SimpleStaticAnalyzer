#include "SPVStore.h"

bool SPVStore::add(shared_ptr<Statement> stmt, shared_ptr<Variable> var) {
    auto stmtType = stmt->getStatementType();
    allStmts[stmt].insert(var);
    // duplicates
    procedureToVar[stmt->getProcedureName()].insert(var);
    switch (stmtType) {
        case EntityType::Assign:assignStmts[stmt].insert(var);
            break;
        case EntityType::Print:printStmts[stmt].insert(var);
            break;
        case EntityType::Call:callStmts[stmt].insert(var);
            break;
        case EntityType::Read:readStmts[stmt].insert(var);
            break;
        case EntityType::If:
        case EntityType::While:ifWhileStmts[stmt].insert(var);
            break;
        default:
            // unknown statement type
            return false;
    }
    return true;
};

vector<vector<shared_ptr<Entity>>> SPVStore::getStmtVarPairs(
    const unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> &table, EntityType type) {
    if (cache.find(type) != cache.end()) {
        return cache[type];
    }
    vector<vector<shared_ptr<Entity>>> res;
    for (auto &v : table) {
        auto stmt1 = v.first;
        for (auto stmt2 : v.second) {
            res.push_back({stmt1, stmt2});
        }
    }
    cache[type] = res;
    return res;
}

vector<vector<shared_ptr<Entity>>> SPVStore::getByType(EntityType entType) {
    switch (entType) {
        case EntityType::Assign: return getStmtVarPairs(assignStmts, entType);
        case EntityType::Print: return getStmtVarPairs(printStmts, entType);
        case EntityType::Read: return getStmtVarPairs(readStmts, entType);
        case EntityType::Call: return getStmtVarPairs(callStmts, entType);
        case EntityType::Stmt: return getStmtVarPairs(allStmts, entType);
        case EntityType::While:
        case EntityType::If: return getStmtVarPairs(ifWhileStmts, EntityType::If);
        case EntityType::Procedure: return getProcVarPairs(procedureToVar);
        default:
            // should throw error
            return {};
    }
}

unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> SPVStore::getAllMap() {
    return allStmts;
}

unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> SPVStore::getReadMap() {
    return readStmts;
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> SPVStore::getPrintMap() {
    return printStmts;
}
unordered_map<string, unordered_set<shared_ptr<Variable>>> SPVStore::getByProcedureMap() {
    return procedureToVar;
}

vector<vector<shared_ptr<Entity>>> SPVStore::getProcVarPairs(
    unordered_map<string, unordered_set<shared_ptr<Variable>>> map) {
    if (procVarCache.size() == 0) {
        for (auto &v : map) {
            auto procName = v.first;
            shared_ptr<Procedure> proc = make_shared<Procedure>(procName);
            for (auto var : v.second) {
                procVarCache.push_back({proc, var});
            }
        }
    }
    return procVarCache;
}

void SPVStore::clear() {
    allStmts.clear();
    assignStmts.clear();
    printStmts.clear();
    readStmts.clear();
    ifWhileStmts.clear();
    callStmts.clear();
    procedureToVar.clear();
    cache.clear();
    procVarCache.clear();
};

SPVStore::~SPVStore() {
    clear();
};