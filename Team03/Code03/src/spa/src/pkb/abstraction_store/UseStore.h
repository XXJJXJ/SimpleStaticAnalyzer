#pragma once

#include "SPVStore.h"

class UseStore : public SPVStore {
public:
    vector<vector<shared_ptr<Entity>>> getByRead() override;
};