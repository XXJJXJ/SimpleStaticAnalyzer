#include "ParentStore.h"


bool ParentStore::add(shared_ptr<Entity> parent, shared_ptr<Entity> child) {
    // Tree like structure
    if (parent == child) {
        // Cannot be parent of itself
        return false;
    }
    auto castedParent = dynamic_pointer_cast<Statement>(parent);
    auto castedChild = dynamic_pointer_cast<Statement>(child);
    if (childToParentMap.find(castedChild) != childToParentMap.end()) {
        // should only have 1 direct parent
        return false;
    }
    if (transitiveMap[child].find(parent) != transitiveMap[child].end()) {
        // Cannot have cycles
        return false;
    }
    directMap[parent].insert(child);
    transitiveMap[parent].insert(child);
    childToParentMap[castedChild] = castedParent;
    // iterate through all parents to craft the transitive map
    // assumes that whatever traversal of the program follows dfs order / is correct
    auto ancestor = castedParent;
    while (childToParentMap.find(ancestor) != childToParentMap.end()) {
        ancestor = childToParentMap[ancestor];
        transitiveMap[ancestor].insert(child);
        // terminates once this ancestor is the "root"
    }
    return true;
}

unordered_map<shared_ptr<Statement>, shared_ptr<Statement>> ParentStore::getChildToParentMap() {
    return childToParentMap;
}

void ParentStore::clear() {
    directMap.clear();
    transitiveMap.clear();
    childToParentMap.clear();
}

ParentStore::~ParentStore() {
    clear();
}