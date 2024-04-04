#include "ParentStore.h"

bool ParentStore::checkValidity(shared_ptr<Statement> parent, shared_ptr<Statement> child) {
    // Tree like structure
    if (parent == child) {
        // Cannot be parent of itself
        return false;
    }
    if (helperMap.find(child) != helperMap.end()) {
        // should only have 1 direct parent
        return false;
    }
    if (transitiveMap[child].find(parent) != transitiveMap[child].end()) {
        // Cannot have cycles
        return false;
    }
    return true;
}

unordered_map<shared_ptr<Statement>, shared_ptr<Statement>> ParentStore::getChildToParentMap() {
    return helperMap;
}

ParentStore::~ParentStore() {
    clear();
}