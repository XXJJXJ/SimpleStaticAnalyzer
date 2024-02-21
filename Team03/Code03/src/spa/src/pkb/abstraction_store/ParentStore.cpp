#include "ParentStore.h"


bool ParentStore::add(shared_ptr<Statement> parent, shared_ptr<Statement> child) {
    // Tree like structure
    if (parent == child) {
        // Cannot be parent of itself
        return false;
    }
    if (childToParentMap.find(child) != childToParentMap.end()) {
        // should only have 1 direct parent
        return false;
    }
    if (transitiveMap[child].find(parent) != transitiveMap[child].end()) {
        // Cannot have cycles
        return false;
    }
    directMap[parent].insert(child);
    transitiveMap[parent].insert(child);
    childToParentMap[child] = parent;
    // iterate through all parents to craft the transitive map
    // assumes that whatever traversal of the program follows dfs order / is correct
    auto ancestor = parent;
    while (childToParentMap.find(ancestor) != childToParentMap.end()) {
        ancestor = childToParentMap[ancestor];
        transitiveMap[ancestor].insert(child);
        // terminates once this ancestor is the "root"
    }
    return true;
}

void ParentStore::clear() {
    directMap.clear();
    transitiveMap.clear();
    childToParentMap.clear();
}

ParentStore::~ParentStore() {
    clear();
}