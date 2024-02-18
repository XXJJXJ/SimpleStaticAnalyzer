#pragma once

#include <set>
#include <unordered_map>
#include "common/Statement.h"
#include "StmtStmtStore.h"

class FollowStore : public StmtStmtStore {
private:
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> directMap;
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> transitiveMap;

    unordered_map<shared_ptr<Statement>, shared_ptr<Statement>> followedToFollowerMap;
public:
    bool add(shared_ptr<Statement> follower, shared_ptr<Statement> followed) override;
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getDirect() override;
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getTransitive() override;
    void clear() override;
    ~FollowStore();
};