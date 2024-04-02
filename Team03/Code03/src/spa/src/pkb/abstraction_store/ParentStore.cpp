#include "ParentStore.h"

// Potential DRY violation with FollowStore (as per MS2): 
// However it is arguably accepted for clarity.
// The childToParentMap here is hard to abstract to a general enough name
// that conveys accurately what it is doing
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

unordered_map<shared_ptr<Statement>, shared_ptr<Statement>> ParentStore::getChildToParentMap() {
    return childToParentMap;
}

void ParentStore::clear() {
    StmtStmtStore::clear();
    childToParentMap.clear();
}

ParentStore::~ParentStore() {
    clear();
}