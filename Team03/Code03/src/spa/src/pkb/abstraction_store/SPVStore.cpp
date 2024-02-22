#include "SPVStore.h"

bool SPVStore::add(shared_ptr<Statement> stmt, shared_ptr<Variable> var) {
    auto stmtType = stmt->getStatementType();
    allStmts[stmt].insert(var);
    // duplicates
    procedureToVar[stmt->getProcedureName()].insert(var);
    switch (stmtType)
    {
    case EntityType::Assign:
        assignStmts[stmt].insert(var);
        break;
    case EntityType::Print:
        printStmts[stmt].insert(var);
        break;
    case EntityType::Call:
        callStmts[stmt].insert(var);
        break;
    case EntityType::Read:
        readStmts[stmt].insert(var);
        break;
    case EntityType::If:
    case EntityType::While:
        ifWhileStmts[stmt].insert(var);
        break;
    default:
        // unknown statement type
        return false;
    }
    return true;
};

vector<vector<shared_ptr<Entity>>> SPVStore::getStmtVarPairs(
    const unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>>& table,
    EntityType type) 
{
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

vector<vector<shared_ptr<Entity>>> SPVStore::getByAssign() {
    return getStmtVarPairs(assignStmts, EntityType::Assign);
}
vector<vector<shared_ptr<Entity>>> SPVStore::getByPrint() {
    return getStmtVarPairs(printStmts, EntityType::Print);
}
vector<vector<shared_ptr<Entity>>> SPVStore::getByRead() {
    return getStmtVarPairs(readStmts, EntityType::Read);
}
vector<vector<shared_ptr<Entity>>> SPVStore::getByIfWhileStmt() {
    return getStmtVarPairs(ifWhileStmts, EntityType::If);
}
vector<vector<shared_ptr<Entity>>> SPVStore::getByCall() {
    return getStmtVarPairs(callStmts, EntityType::Call);
}
vector<vector<shared_ptr<Entity>>> SPVStore::getByAllStmt() {
    return getStmtVarPairs(allStmts, EntityType::Stmt);
}

unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> SPVStore::getAllMap() {
    return allStmts;
}

unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> SPVStore::getReadMap() {
    return readStmts;
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> SPVStore::getPrintMap() {
    return printStmts;
}
unordered_map<string, set<shared_ptr<Variable>>> SPVStore::getByProcedureMap() {
    return procedureToVar;
}

void SPVStore::clear() {
    allStmts.clear();
    assignStmts.clear();
    printStmts.clear();
    readStmts.clear();
    ifWhileStmts.clear();
    callStmts.clear();
    procedureToVar.clear();
};
SPVStore::~SPVStore() {
    clear();
};