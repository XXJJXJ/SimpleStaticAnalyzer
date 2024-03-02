#pragma once

#include <unordered_map>
#include "common/Statement.h"
#include "DirectTransitiveStore.h"

class FollowStore : public DirectTransitiveStore {
private:
    unordered_map<shared_ptr<Entity>, shared_ptr<Entity>> followedToFollowerMap;
public:
    bool add(shared_ptr<Entity> follower, shared_ptr<Entity> followed) override;
    void clear() override;
    ~FollowStore();
};