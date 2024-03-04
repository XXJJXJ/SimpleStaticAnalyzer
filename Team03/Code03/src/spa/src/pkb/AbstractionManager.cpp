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

bool AbstractionManager::addCalls(shared_ptr<Procedure> proc1, shared_ptr<Procedure> proc2) {
    return callStore.add(proc1, proc2);
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

void AbstractionManager::tabulate() {
    tabulateContainerStmtVarRelation(useStore);
    tabulateContainerStmtVarRelation(modifyStore);
    callStore.tabulate();
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

vector<vector<shared_ptr<Entity>>> AbstractionManager::getUseByType(EntityType entType) {
    return useStore.getByType(entType);
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getModifyByType(EntityType entType) {
    return modifyStore.getByType(entType);
}

unordered_map<string, unordered_set<shared_ptr<Variable>>> AbstractionManager::getUseByProcedureMap() {
    return useStore.getByProcedureMap();
}
unordered_map<string, unordered_set<shared_ptr<Variable>>> AbstractionManager::getModifyByProcedureMap() {
    return modifyStore.getByProcedureMap();
}


// For testing
unordered_map<shared_ptr<Entity>, unordered_set<shared_ptr<Entity>>> AbstractionManager::getFollowSMap() {
    return followStore.getDirectMap();
}
unordered_map<shared_ptr<Entity>, unordered_set<shared_ptr<Entity>>> AbstractionManager::getFollowTMap() {
    return followStore.getTransitiveMap();
}
unordered_map<shared_ptr<Entity>, unordered_set<shared_ptr<Entity>>> AbstractionManager::getParentSMap() {
    return parentStore.getDirectMap();
}
unordered_map<shared_ptr<Entity>, unordered_set<shared_ptr<Entity>>> AbstractionManager::getParentTMap() {
    return parentStore.getTransitiveMap();
}

unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> AbstractionManager::getUseAllMap() {
    return useStore.getAllMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> AbstractionManager::getUseByPrintMap() {
    return useStore.getPrintMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> AbstractionManager::getModifyAllMap() {
    return modifyStore.getAllMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> AbstractionManager::getModifyByReadMap() {
    return modifyStore.getReadMap();
}


AbstractionManager::~AbstractionManager() {
    clear();
}