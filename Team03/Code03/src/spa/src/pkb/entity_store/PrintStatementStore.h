#pragma once

#include "common/PrintStatement.h"
#include "pkb/StoreInterface.h"


class PrintStatementStore : public StoreInterface<PrintStatement> {
private:
    unordered_map<int, shared_ptr<PrintStatement>> lineToPrintStatementMap;
public:
    PrintStatementStore();
    bool add(shared_ptr<PrintStatement> stmt) override;
    vector<shared_ptr<PrintStatement>> getAll() const override;
    void clear() override;
    ~PrintStatementStore();
};