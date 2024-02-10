#pragma once
#include <string>
#include <vector>
#include "common/Procedure.h"
#include "StoreInterface.h"

class ProcedureStore : public StoreInterface<Procedure> {
private:
    std::unordered_map<string, shared_ptr<Procedure>> nameToProcMap;
public:
    bool add(shared_ptr<Procedure> procedure) override;
    vector<shared_ptr<Procedure>> getAll() const override;
    void clear() override;
    ~ProcedureStore() override;
};