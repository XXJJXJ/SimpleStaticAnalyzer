#pragma once

#include <unordered_map>

#include "common/Statement.h"
#include "DirectTransitiveStore.h"

class ParentStore : public DirectTransitiveStore {
private:
    unordered_map<shared_ptr<Statement>, shared_ptr<Statement>> childToParentMap;
public:
    bool add(shared_ptr<Entity> parent, shared_ptr<Entity> child) override;
    void clear() override;
    ~ParentStore();
    // For internal use, not exposed to SP or QPS
    unordered_map<shared_ptr<Statement>, shared_ptr<Statement>> getChildToParentMap();
};