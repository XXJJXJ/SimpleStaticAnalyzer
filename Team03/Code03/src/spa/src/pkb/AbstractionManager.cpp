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
};

unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> AbstractionManager::getFollowS() {
    return followStore.getDirect();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> AbstractionManager::getFollowT() {
    return followStore.getTransitive();
}

unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> AbstractionManager::getParentS() {
    return parentStore.getDirect();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> AbstractionManager::getParentT() {
    return parentStore.getTransitive();
}

unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getUseByAssign() {
    return useStore.getByAssign();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getUseByPrint() {
    return useStore.getByPrint();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getUseByCall() {
    return useStore.getByCall();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getUseByIfWhile() {
    return useStore.getByIfWhileStmt();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getUseAll() {
    return useStore.getByAllStmt();
}
unordered_map<string, set<shared_ptr<Variable>>> AbstractionManager::getUseByProcedure() {
    return useStore.getByProcedure();
}

unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getModifyByAssign() {
    return modifyStore.getByAssign();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getModifyByRead() {
    return modifyStore.getByRead();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getModifyByCall() {
    return modifyStore.getByCall();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getModifyByIfWhile() {
    return modifyStore.getByIfWhileStmt();
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> AbstractionManager::getModifyAll() {
    return modifyStore.getByAllStmt();
}
unordered_map<string, set<shared_ptr<Variable>>> AbstractionManager::getModifyByProcedure() {
    return modifyStore.getByProcedure();
}

AbstractionManager::~AbstractionManager() {
    clear();
}