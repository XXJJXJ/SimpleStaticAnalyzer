#include "QueryPKB.h"

QueryManager::QueryManager() {
    am = AbstractionManager::getInstance();
    em = EntityManager::getInstance();
    pm = PatternManager::getInstance();
}

void QueryManager::clear() {
    EntityManager::clear();
    AbstractionManager::clear();
    PatternManager::clear();
    procVarResultCache.clear();
}

vector<shared_ptr<Entity>> QueryManager::getAllConstants() {
    return em->getAllConstants();
}

vector<shared_ptr<Entity>> QueryManager::getAllVariables() {
    return em->getAllVariables();
}

shared_ptr<Entity> QueryManager::getVariableByName(string var) {
    return em->getVariableByName(var);
}

vector<shared_ptr<Procedure>> QueryManager::getAllProcedures() {
    return em->getAllProcedures();
}

vector<shared_ptr<PrintStatement>> QueryManager::getAllPrintStatements() {
    return em->getAllPrintStatements();
}

vector<shared_ptr<ReadStatement>> QueryManager::getAllReadStatements() {
    return em->getAllReadStatements();
}

vector<shared_ptr<Statement>> QueryManager::getAllStatements() {
    return em->getAllStatements();
}

vector<shared_ptr<AssignStatement>> QueryManager::getAllAssignStatements() {
    return em->getAllAssignStatements();
}

vector<shared_ptr<CallStatement>> QueryManager::getAllCallStatements() {
    return em->getAllCallStatements();
}

vector<shared_ptr<IfStatement>> QueryManager::getAllIfStatements() {
    return em->getAllIfStatements();
}

vector<shared_ptr<WhileStatement>> QueryManager::getAllWhileStatements() {
    return em->getAllWhileStatements();
}

// Abstractions
vector<vector<shared_ptr<Entity>>> QueryManager::getFollowS() {
    return am->getFollowS();
}
vector<vector<shared_ptr<Entity>>> QueryManager::getFollowT() {
    return am->getFollowT();
}

vector<vector<shared_ptr<Entity>>> QueryManager::getParentS() {
    return am->getParentS();
}
vector<vector<shared_ptr<Entity>>> QueryManager::getParentT() {
    return am->getParentT();
}
vector<vector<shared_ptr<Entity>>> QueryManager::getUseByType(EntityType entType) {
    return am->getUseByType(entType);
}
vector<vector<shared_ptr<Entity>>> QueryManager::getUseByProcedure() {
    const string uses = "uses";
    if (procVarResultCache.find(uses) != procVarResultCache.end()) {
        return procVarResultCache[uses];
    }
    auto procUseMap = am->getUseByProcedureMap();
    vector<vector<shared_ptr<Entity>>> res;
    for (auto &_pair : procUseMap) {
        auto proc = em->getProcByName(_pair.first);
        for (auto &var : _pair.second) {
            res.push_back({proc, var});
        }
    }
    procVarResultCache[uses] = res;
    return res;
}

vector<vector<shared_ptr<Entity>>> QueryManager::getModifyByType(EntityType entType) {
    return am->getModifyByType(entType);
}
vector<vector<shared_ptr<Entity>>> QueryManager::getModifyByProcedure() {
    const string modifies = "modifies";
    if (procVarResultCache.find(modifies) != procVarResultCache.end()) {
        return procVarResultCache[modifies];
    }
    auto procModifyMap = am->getModifyByProcedureMap();
    vector<vector<shared_ptr<Entity>>> res;
    for (auto &_pair : procModifyMap) {
        auto proc = em->getProcByName(_pair.first);
        for (auto &var : _pair.second) {
            res.push_back({proc, var});
        }
    }
    procVarResultCache[modifies] = res;
    return res;
}

vector<vector<shared_ptr<Entity>>> QueryManager::getCallS() {
    return am->getCallS();
}
vector<vector<shared_ptr<Entity>>> QueryManager::getCallT() {
    return am->getCallT();
}

vector<vector<shared_ptr<Entity>>> QueryManager::getNextS() {
    return am->getNextS();
}
vector<vector<shared_ptr<Entity>>> QueryManager::getNextT() {
    return am->getNextT();
}

bool QueryManager::checkLayer(
    shared_ptr<AssignStatement> a2,
    shared_ptr<Variable> targetVar,
    vector<shared_ptr<Statement>> &nextLayer,
    unordered_set<shared_ptr<Statement>> &visited,
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> &nextTMap
) {
    auto nextSMap = am->getNextSMap();
    auto modifyStore = am->getModifyAllMap();
    vector<shared_ptr<Statement>> newLayer;
    for (auto s : nextLayer) {
        for (auto n : nextSMap[s]) {
            if (n->getStatementNumber() == a2->getStatementNumber()) {
                // if reached here, a path with no modifies is found
                return true;
            }
            if (visited.find(n) != visited.end()) {
                continue;
            }
            if ((n->isOfType(EntityType::If) ||  // if statement does not actually modify (but inherits from child); OR
                n->isOfType(EntityType::While) || // while statement likewise, can pass; OR
                modifyStore.find(n) == modifyStore.end() || // if it does not modify; OR
                modifyStore[n].find(targetVar) == modifyStore[n].end()) // does not modify target variable
                && nextTMap[n].find(a2) != nextTMap[n].end())  // AND it will eventually reach a2
            {
                // then add this statement to newLayer to be traversed later
                newLayer.push_back(n);
                visited.insert(n);
            }
        }
    }
    nextLayer = newLayer;
    return false;
}

// Helper function for affects
bool QueryManager::hasNotModifiedPath(
    shared_ptr<AssignStatement> a1,
    shared_ptr<AssignStatement> a2,
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> &nextTMap) {
    // do a bfs traverse, initialize starting layer
    vector<shared_ptr<Statement>> nextLayer = {a1};
    shared_ptr<Variable> targetVar = a1->getVariable();
    // Avoid looping on a while loop
    unordered_set<shared_ptr<Statement>> visited;
    while (nextLayer.size() > 0) {
        if (checkLayer(a2, targetVar, nextLayer, visited, nextTMap)) {
            return true;
        }
    }
    return false;
}

// Affects: On the spot calculation using information from all the stores
vector<vector<shared_ptr<Entity>>> QueryManager::getAffects() {
    auto nextTMap = am->getNextTMap();
    auto nextT = StmtStmtStore::getStmtPairs(nextTMap);
    auto useStore = am->getUseAllMap(); // map of stmt to unordered_set of variables
    /*  filter nextT for assign - assign statement pairs (a1, a2)
        that exists a variable such that a1 modifies v [from assignstatement itself]
        and a2 uses v
    */
    vector<vector<shared_ptr<AssignStatement>>> filteredForRelatedAssigns;
    for (auto &_p : nextT) {
        if (_p[0]->isOfType(EntityType::Assign) && _p[1]->isOfType(EntityType::Assign)) {
            auto a1 = dynamic_pointer_cast<AssignStatement>(_p[0]);
            auto a2 = dynamic_pointer_cast<AssignStatement>(_p[1]);
            if (useStore[a2].find(a1->getVariable()) != useStore[a2].end()) {
                filteredForRelatedAssigns.push_back({a1, a2});
            }

        }
    }
    // if there exist a path from a1 to a2 such that v is not modified, insert into results
    vector<vector<shared_ptr<Entity>>> results;
    for (auto _ap : filteredForRelatedAssigns) {
        if (hasNotModifiedPath(_ap[0], _ap[1], nextTMap)) {
            results.push_back({_ap[0], _ap[1]});
        }
    }
    return results;
}

unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> QueryManager::getFollowSMap() {
    return am->getFollowSMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> QueryManager::getFollowTMap() {
    return am->getFollowTMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> QueryManager::getParentSMap() {
    return am->getParentSMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> QueryManager::getParentTMap() {
    return am->getParentTMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> QueryManager::getUseAllMap() {
    return am->getUseAllMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> QueryManager::getUseByPrintMap() {
    return am->getUseByPrintMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> QueryManager::getModifyAllMap() {
    return am->getModifyAllMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> QueryManager::getModifyByReadMap() {
    return am->getModifyByReadMap();
}
unordered_map<string, unordered_set<shared_ptr<Variable>>> QueryManager::getUseByProcedureMap() {
    return am->getUseByProcedureMap();
}
unordered_map<string, unordered_set<shared_ptr<Variable>>> QueryManager::getModifyByProcedureMap() {
    return am->getModifyByProcedureMap();
}

vector<vector<shared_ptr<Entity>>> QueryManager::getAssignPattern(string expr, bool hasWildcard) {
    if (pm->hasAssignPattern(expr, hasWildcard)) {
        return pm->getAssignPattern(expr, hasWildcard);
    } else {
        auto allAssign = em->getAllAssignStatements();
        return pm->findAssignPattern(allAssign, expr, hasWildcard); // will cache results
    }
}

vector<vector<shared_ptr<Entity>>> QueryManager::getIfPattern() {
    return pm->getIfPattern();
}

vector<vector<shared_ptr<Entity>>> QueryManager::getWhilePattern() {
    return pm->getWhilePattern();
}

vector<shared_ptr<Entity>> QueryManager::getAllEntitiesByType(EntityType entityType) {
    vector<shared_ptr<Entity>> baseClassEntities;

    auto addEntities = [&](auto &&entities) {
      baseClassEntities.insert(baseClassEntities.end(), entities.begin(), entities.end());
    };

    switch (entityType) {
        case EntityType::Procedure: addEntities(getAllProcedures());
            break;
        case EntityType::Stmt: addEntities(getAllStatements());
            break;
        case EntityType::Assign: addEntities(getAllAssignStatements());
            break;
        case EntityType::Print: addEntities(getAllPrintStatements());
            break;
        case EntityType::Read: addEntities(getAllReadStatements());
            break;
        case EntityType::Call: addEntities(getAllCallStatements());
            break;
        case EntityType::If: addEntities(getAllIfStatements());
            break;
        case EntityType::While: addEntities(getAllWhileStatements());
            break;
        case EntityType::Variable: addEntities(getAllVariables());
            break;
        case EntityType::Constant: addEntities(getAllConstants());
            break;
        default: throw std::invalid_argument("Unknown entity type");
    }

    return baseClassEntities;
}
