#pragma once

#include <unordered_map>

#include "common/Statement.h"
#include "StmtStmtStore.h"

class ParentStore : public StmtStmtStore {
private:
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> directMap;
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> transitiveMap;
    unordered_map<shared_ptr<Statement>, shared_ptr<Statement>> childToParentMap;
public:
    bool add(shared_ptr<Statement> parent, shared_ptr<Statement> child) override;
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getDirect() override;
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getTransitive() override;
    void clear() override;
    ~ParentStore();
};