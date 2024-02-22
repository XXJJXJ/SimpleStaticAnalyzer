#include "AbstractionManager.h"

shared_ptr<AbstractionManager> AbstractionManager::instance = nullptr;

shared_ptr<AbstractionManager> AbstractionManager::getInstance() {
    if (!instance) {
        AbstractionManager* em = new AbstractionManager();
        instance = make_shared<AbstractionManager>(*em);
    }
    return instance;
}

void AbstractionManager::clear() {
    if (!instance) {
        return;
    }
    instance->clearStore();
}

void AbstractionManager::clearStore() {
    modifyStore.clear();
    useStore.clear();
    followStore.clear();
    parentStore.clear();
}

bool AbstractionManager::addFollow(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
    return followStore.add(stmt1, stmt2);
}

bool AbstractionManager::addParent(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
    return parentStore.add(stmt1, stmt2);
}

bool AbstractionManager::addUses(shared_ptr<Statement> stmt, shared_ptr<Variable> var) {
    return useStore.add(stmt, var);
}

bool AbstractionManager::addModifies(shared_ptr<Statement> stmt, shared_ptr<Variable> var) {
    return modifyStore.add(stmt, var);
}

// Private helper function
void AbstractionManager::tabulateContainerStmtVarRelation(SPVStore& store) {
    auto childToParent = parentStore.getChildToParentMap();
    auto allRelations = store.getAllMap();
    for (auto & _pair : allRelations) {
        for (auto & _var : _pair.second) {
            auto ancestor = _pair.first;
            while (childToParent.find(ancestor) != childToParent.end()) {
                // Can modify first, because the first statement is already stored
                ancestor = childToParent[ancestor];
                store.add(ancestor, _var);
            }
        }
    }
}

void AbstractionManager::tabulateUses() {
    tabulateContainerStmtVarRelation(useStore);
}

void AbstractionManager::tabulateModifies() {
    tabulateContainerStmtVarRelation(modifyStore);
}


vector<vector<shared_ptr<Entity>>> AbstractionManager::getFollowS() {
    return followStore.getDirect();
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getFollowT() {
    return followStore.getTransitive();
}

vector<vector<shared_ptr<Entity>>> AbstractionManager::getParentS() {
    return parentStore.getDirect();
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getParentT() {
    return parentStore.getTransitive();
}

vector<vector<shared_ptr<Entity>>> AbstractionManager::getUseByAssign() {
    return useStore.getByAssign();
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getUseByPrint() {
    return useStore.getByPrint();
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getUseByCall() {
    return useStore.getByCall();
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getUseByIfWhile() {
    return useStore.getByIfWhileStmt();
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getUseAll() {
    return useStore.getByAllStmt();
}
unordered_map<string, set<shared_ptr<Variable>>> AbstractionManager::getUseByProcedure() {
    return useStore.getByProcedure();
}

vector<vector<shared_ptr<Entity>>> AbstractionManager::getModifyByAssign() {
    return modifyStore.getByAssign();
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getModifyByRead() {
    return modifyStore.getByRead();
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getModifyByCall() {
    return modifyStore.getByCall();
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getModifyByIfWhile() {
    return modifyStore.getByIfWhileStmt();
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getModifyAll() {
    return modifyStore.getByAllStmt();
}
unordered_map<string, set<shared_ptr<Variable>>> AbstractionManager::getModifyByProcedure() {
    return modifyStore.getByProcedure();
}


// For testing
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> AbstractionManager::getFollowSMap() {
    return followStore.getDirectMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> AbstractionManager::getFollowTMap() {
    return followStore.getTransitiveMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> AbstractionManager::getParentSMap() {
    return parentStore.getDirectMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> AbstractionManager::getParentTMap() {
    return parentStore.getTransitiveMap();
}

unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getUseAllMap() {
    return useStore.getAllMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getUseByPrintMap() {
    return useStore.getPrintMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getModifyAllMap() {
    return modifyStore.getAllMap();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getModifyByReadMap() {
    return modifyStore.getReadMap();
}

AbstractionManager::~AbstractionManager() {
    clear();
}