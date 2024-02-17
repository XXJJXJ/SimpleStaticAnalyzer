#pragma once

#include "SPVStore.h"

class UseStore : public SPVStore {
public:
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getByRead() override;
};