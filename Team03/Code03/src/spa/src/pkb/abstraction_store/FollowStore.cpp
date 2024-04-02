#include "FollowStore.h"

// Potential DRY violation with ParentStore (as per MS2): 
// However it is arguably accepted for clarity.
// The followedToFollowerMap here is hard to abstract to a general enough name
// that conveys accurately what it is doing
bool FollowStore::add(shared_ptr<Statement> follower, shared_ptr<Statement> followed) {
    if (directMap.find(follower) != directMap.end()) {
        // can only follow 1 stmt, already following something
        return false;
    }
    if (followedToFollowerMap.find(followed) != followedToFollowerMap.end()) {
        // should only have 1 direct follower
        return false;
    }
    // Detect cycles
    if (transitiveMap[followed].find(follower) != transitiveMap[followed].end()) {
        // Cannot have cycles
        return false;
    }
    directMap[follower].insert(followed);
    transitiveMap[follower].insert(followed);
    followedToFollowerMap[followed] = follower;
    // iterate through all ancestor to craft the transitive map
    // assumes that whatever traversal of the program follows dfs order / is correct
    auto ancestor = follower;
    while (followedToFollowerMap.find(ancestor) != followedToFollowerMap.end()) {
        ancestor = followedToFollowerMap[ancestor];
        transitiveMap[ancestor].insert(followed);
        // terminates once this ancestor is the "root"
    }
    return true;
}

void FollowStore::clear() {
    StmtStmtStore::clear();
    followedToFollowerMap.clear();
}

FollowStore::~FollowStore() {
    clear();
}