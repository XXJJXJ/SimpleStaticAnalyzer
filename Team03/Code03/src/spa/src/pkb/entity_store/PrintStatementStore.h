#pragma once

#include "common/PrintStatement.h"
#include "EntityStoreInterface.h"


class PrintStatementStore : public EntityStoreInterface<PrintStatement> {
private:
    unordered_map<int, shared_ptr<PrintStatement>> lineToPrintStatementMap;
public:
    PrintStatementStore();
    bool add(shared_ptr<PrintStatement> stmt) override;
    vector<shared_ptr<PrintStatement>> getAll() const override;
    void clear() override;
    ~PrintStatementStore();
};