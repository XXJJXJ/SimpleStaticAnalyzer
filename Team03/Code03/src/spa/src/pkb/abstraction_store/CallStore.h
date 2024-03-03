#pragma once

#include <unordered_map>
#include "common/Entity.h"
#include "common/Procedure.h"
#include "common/spa_exception/SemanticErrorException.h"
#include "DirectTransitiveStore.h"

// Notes: A procedure may be called by multiple procedures
// Itself can also call multiple procedures
class CallStore : public DirectTransitiveStore {
private:
    // Private helper
    unordered_set<shared_ptr<Entity>> dfsAdd(shared_ptr<Entity> proc);
public:
    bool add(shared_ptr<Entity> follower, shared_ptr<Entity> followed) override;
    void clear() override;
    void tabulate();
    ~CallStore();
};