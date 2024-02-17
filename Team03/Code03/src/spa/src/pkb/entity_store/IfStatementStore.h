#pragma once

#include <unordered_map>

#include "common/IfStatement.h"
#include "EntityStoreInterface.h"

class IfStatementStore : public EntityStoreInterface<IfStatement> {
private:
    unordered_map<int, shared_ptr<IfStatement>> lineToIfStatementMap;
public:
    IfStatementStore();
    bool add(shared_ptr<IfStatement> stmt) override;
    vector<shared_ptr<IfStatement>> getAll() const override;
    void clear() override;
    ~IfStatementStore();
};