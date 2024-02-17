#include "FollowStore.h"

bool FollowStore::add(shared_ptr<Statement> follower, shared_ptr<Statement> followed) {
    if (directMap.find(follower) != directMap.end()) {
        // can only follow 1 stmt, already following something
        return false;
    }
    if (followedToFollowerMap.find(followed) != followedToFollowerMap.end()) {
        // should only have 1 direct follower
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

unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> FollowStore::getDirect() {
    return directMap;
}
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> FollowStore::getTransitive() {
    return transitiveMap;
}

void FollowStore::clear() {
    directMap.clear();
    transitiveMap.clear();
    followedToFollowerMap.clear();
}

FollowStore::~FollowStore() {
    clear();
}