#pragma once

#include <set>
#include <unordered_map>
#include "common/Statement.h"
#include "StmtStmtStore.h"

class FollowStore : public StmtStmtStore {
private:
    unordered_map<shared_ptr<Statement>, shared_ptr<Statement>> followedToFollowerMap;
public:
    bool add(shared_ptr<Statement> follower, shared_ptr<Statement> followed) override;
    void clear() override;
    ~FollowStore();
};