#include "QueryPKB.h"

QueryManager::QueryManager () {
    am = AbstractionManager::getInstance();
    em = EntityManager::getInstance();
    pm = PatternManager::getInstance();
}

void QueryManager::clear() {
    EntityManager::clear();
    AbstractionManager::clear();
    PatternManager::clear();
}

vector<shared_ptr<Constant>> QueryManager::getAllConstants() {
    return em->getAllConstants();
}

vector<shared_ptr<Variable>> QueryManager::getAllVariables() {
    return em->getAllVariables();
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

vector<vector<shared_ptr<Entity>>> QueryManager::getUseByAssign() {
    return am->getUseByAssign();
}
vector<vector<shared_ptr<Entity>>> QueryManager::getUseByPrint() {
    return am->getUseByPrint();
}
vector<vector<shared_ptr<Entity>>>QueryManager::getUseByCall() {
    return am->getUseByCall();
}
vector<vector<shared_ptr<Entity>>> QueryManager::getUseByIfWhile() {
    return am->getUseByIfWhile();
}
vector<vector<shared_ptr<Entity>>>QueryManager::getUseAll() {
    return am->getUseAll();
}
unordered_map<string, set<shared_ptr<Variable>>> QueryManager::getUseByProcedure() {
    return am->getUseByProcedure();
}

vector<vector<shared_ptr<Entity>>> QueryManager::getModifyByAssign() {
    return am->getModifyByAssign();
}
vector<vector<shared_ptr<Entity>>> QueryManager::getModifyByRead() {
    return am->getModifyByRead();
}
vector<vector<shared_ptr<Entity>>> QueryManager::getModifyByCall() {
    return am->getModifyByCall();
}
vector<vector<shared_ptr<Entity>>> QueryManager::getModifyByIfWhile() {
    return am->getModifyByIfWhile();
}
vector<vector<shared_ptr<Entity>>> QueryManager::getModifyAll() {
    return am->getModifyAll();
}
unordered_map<string, set<shared_ptr<Variable>>> QueryManager::getModifyByProcedure() {
    return am->getModifyByProcedure();
}

unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> QueryManager::getFollowSMap() {
    return am->getFollowSMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> QueryManager::getFollowTMap() {
    return am->getFollowTMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> QueryManager::getParentSMap() {
    return am->getParentSMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> QueryManager::getParentTMap() {
    return am->getParentTMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getUseAllMap() {
    return am->getUseAllMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getUseByPrintMap() {
    return am->getUseByPrintMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getModifyAllMap() {
    return am->getModifyAllMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getModifyByReadMap() {
    return am->getModifyByReadMap();
}


vector<shared_ptr<AssignStatement>> QueryManager::getAssignPattern(string targetVariable, string expr, bool hasWildcard) {
    if (pm->hasAssignPattern(expr, hasWildcard)) {
        return pm->getAssignPattern(targetVariable, expr, hasWildcard);
    } else {
        auto allAssign = em->getAllAssignStatements();
        return pm->findAssignPattern(allAssign, targetVariable, expr, hasWildcard); // will cache results
    }
}

vector<shared_ptr<Entity>> QueryManager::getAllEntitiesByType(EntityType entityType) {
    vector<shared_ptr<Entity>> baseClassEntities;

    auto addEntities = [&](auto&& entities) {
        baseClassEntities.insert(baseClassEntities.end(), entities.begin(), entities.end());
    };

    switch (entityType) {
        case EntityType::Procedure: addEntities(getAllProcedures()); break;
        case EntityType::Stmt: addEntities(getAllStatements()); break;
        case EntityType::Assign: addEntities(getAllAssignStatements()); break;
        case EntityType::Print: addEntities(getAllPrintStatements()); break;
        case EntityType::Read: addEntities(getAllReadStatements()); break;
        case EntityType::Call: addEntities(getAllCallStatements()); break;
        case EntityType::If: addEntities(getAllIfStatements()); break;
        case EntityType::While: addEntities(getAllWhileStatements()); break;
        case EntityType::Variable: addEntities(getAllVariables()); break;
        default: throw std::invalid_argument("Unknown entity type");
    }

    return baseClassEntities;
}
