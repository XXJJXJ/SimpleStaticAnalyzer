#include "FollowStore.h"

bool FollowStore::checkValidity(shared_ptr<Statement> follower, shared_ptr<Statement> followed) {
    if (directMap.find(follower) != directMap.end()) {
        // can only follow 1 stmt, already following something
        return false;
    }
    if (helperMap.find(followed) != helperMap.end()) {
        // should only have 1 direct follower
        return false;
    }
    // Detect cycles
    if (transitiveMap[followed].find(follower) != transitiveMap[followed].end()) {
        // Cannot have cycles
        return false;
    }
    return true;
}

FollowStore::~FollowStore() {
    clear();
}