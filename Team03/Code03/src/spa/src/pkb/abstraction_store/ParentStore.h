#pragma once

#include <unordered_map>

#include "common/statement/Statement.h"
#include "StmtStmtStore.h"

class ParentStore : public StmtStmtStore {
public:
    bool checkValidity(shared_ptr<Statement> parent, shared_ptr<Statement> child) override;
    ~ParentStore();
    // For internal use, not exposed to SP or QPS
    unordered_map<shared_ptr<Statement>, shared_ptr<Statement>> getChildToParentMap();
};