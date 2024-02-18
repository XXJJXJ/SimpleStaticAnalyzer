#pragma once

#include <unordered_map>

#include "common/WhileStatement.h"
#include "EntityStoreInterface.h"

class WhileStatementStore : public EntityStoreInterface<WhileStatement> {
private:
    unordered_map<int, shared_ptr<WhileStatement>> lineToWhileStatementMap;
public:
    WhileStatementStore();
    bool add(shared_ptr<WhileStatement> stmt) override;
    vector<shared_ptr<WhileStatement>> getAll() const override;
    void clear() override;
    ~WhileStatementStore();
};