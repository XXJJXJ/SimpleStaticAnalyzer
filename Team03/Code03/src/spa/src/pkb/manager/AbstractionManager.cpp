#include "AbstractionManager.h"

shared_ptr<AbstractionManager> AbstractionManager::instance = nullptr;

shared_ptr<AbstractionManager> AbstractionManager::getInstance() {
    if (!instance) {
        AbstractionManager *em = new AbstractionManager();
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
    callStore.clear();
    nextStore.clear();
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

bool AbstractionManager::addNext(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
    return nextStore.add(stmt1, stmt2);
}

// Private helper function
void AbstractionManager::tabulateContainerStmtVarRelation(SPVStore &store) {
    auto childToParent = parentStore.getChildToParentMap();
    auto allRelations = store.getAllMap();
    for (auto &_pair : allRelations) {
        for (auto &_var : _pair.second) {
            auto ancestor = _pair.first;
            while (childToParent.find(ancestor) != childToParent.end()) {
                // Can modify first, because the first statement is already stored
                ancestor = childToParent[ancestor];
                store.add(ancestor, _var);
            }
        }
    }
}

void AbstractionManager::tabulateByCallStatements(SPVStore &store, vector<shared_ptr<CallStatement>> &callStmts) {
    auto procVarMap = store.getByProcedureMap();
    auto callMap = callStore.getTransitiveMap();
    unordered_map<string, unordered_set<string>> callMapString;
    for (auto &_pair : callMap) {
        for (auto &callee : _pair.second) {
            callMapString[_pair.first->getName()].insert(callee->getName());
        }
    }
    // get each callStmt - find out the chain/all procedures invoked by the target procedure
    for (auto &stmt : callStmts) {
        // Potential to bugs / slowness
        // **** Order of adding very important ****
        // This gets all the transitive procedures under the called procedures and adds all possible
        // modifies / uses variables to this statement
        // This way the order of adding shouldn't matter anymore
        auto allProcsCalled = callMapString[stmt->getTargetProcedureName()];
        for (auto &proc : allProcsCalled) {
            auto setOfVar = procVarMap[proc];
            for (auto &var : setOfVar) {
                store.add(stmt, var);
            }
        }
        // dont forget the targetProcedure itself might have uses / modifies
        auto setOfVar = procVarMap[stmt->getTargetProcedureName()];
        for (auto &var : setOfVar) {
            store.add(stmt, var);
        }
    }
}

void AbstractionManager::tabulate(vector<shared_ptr<CallStatement>> &callStmts) {
    // tabulate call store first
    callStore.tabulate();
    tabulateByCallStatements(useStore, callStmts);
    tabulateByCallStatements(modifyStore, callStmts);
    tabulateContainerStmtVarRelation(useStore);
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

vector<vector<shared_ptr<Entity>>> AbstractionManager::getCallS() {
    return callStore.getDirect();
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getCallT() {
    return callStore.getTransitive();
}

vector<vector<shared_ptr<Entity>>> AbstractionManager::getNextS() {
    return nextStore.getDirect();
}
vector<vector<shared_ptr<Entity>>> AbstractionManager::getNextT() {
    return nextStore.getTransitive();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> AbstractionManager::getNextSMap() {
    return nextStore.getDirectMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> AbstractionManager::getNextTMap() {
    return nextStore.getTransitiveMap();
}

// For testing
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> AbstractionManager::getFollowSMap() {
    return followStore.getDirectMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> AbstractionManager::getFollowTMap() {
    return followStore.getTransitiveMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> AbstractionManager::getParentSMap() {
    return parentStore.getDirectMap();
}
unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> AbstractionManager::getParentTMap() {
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