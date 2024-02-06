#include <vector>
#include "EntityManager.h"

// Initialize the static instance to nullptr
EntityManager* EntityManager::instance = nullptr;

// Implementation of Entity methods

// Implementation of EntityManager methods
EntityManager* EntityManager::getInstance() {
    if (!instance) {
        instance = new EntityManager();
    }
    return instance;
}


EntityManager::~EntityManager() {
    delete instance;
}

bool EntityManager::addConstant(Constant* c) {
    constantStore.add(c);
    return true;
}

vector<Constant*> EntityManager::getAllConstants() {
    return constantStore.getAll();
}

void EntityManager::clear() {
    if (!instance) {
        return;
    }
    instance->clearStore();
}

void EntityManager::clearStore() {
    constantStore.clear();
    variableStore.clear();
}