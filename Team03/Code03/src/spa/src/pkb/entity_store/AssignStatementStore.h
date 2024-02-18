#pragma once

#include <unordered_map>

#include "common/AssignStatement.h"
#include "EntityStoreInterface.h"

class AssignStatementStore : EntityStoreInterface<AssignStatement> {
private:
    unordered_map<int, shared_ptr<AssignStatement>> lineToAssignStatementMap;
public:
    AssignStatementStore();
    bool add(shared_ptr<AssignStatement> stmt) override;
    vector<shared_ptr<AssignStatement>> getAll() const override;
    void clear() override;
    ~AssignStatementStore();
};