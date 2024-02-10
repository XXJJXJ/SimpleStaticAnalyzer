#pragma once

#include "common/Statement.h"
#include "pkb/StoreInterface.h"


class StatementStore : public StoreInterface<Statement> {
private:
    unordered_map<int, shared_ptr<Statement>> lineToStatementMap;
public:
    StatementStore();
    bool add(shared_ptr<Statement> stmt) override;
    vector<shared_ptr<Statement>> getAll() const override;
    void clear() override;
    ~StatementStore();
};