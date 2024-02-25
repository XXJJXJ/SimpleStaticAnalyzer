#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "common/Procedure.h"
#include "EntityStoreInterface.h"

class ProcedureStore : public EntityStoreInterface<Procedure> {
private:
    unordered_map<string, shared_ptr<Procedure>> nameToProcMap;
public:
    bool add(shared_ptr<Procedure> procedure) override;
    vector<shared_ptr<Procedure>> getAll() const override;

    // Internal API not exposed to SP or QPS
    shared_ptr<Procedure> getProcByName(const string& name);
    void clear() override;
    ~ProcedureStore();
};