#pragma once

#include "common/ReadStatement.h"
#include "pkb/StoreInterface.h"

using namespace std;

class ReadStatementStore : public StoreInterface<ReadStatement> {
private:
    unordered_map<int, shared_ptr<ReadStatement>> lineToReadStatementMap;
public:
    ReadStatementStore();
    bool add(shared_ptr<ReadStatement> stmt) override;
    vector<shared_ptr<ReadStatement>> getAll() const override;
    void clear() override;
    ~ReadStatementStore();
};