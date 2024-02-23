#pragma once

#include "SPVStore.h"

class ModifyStore : public SPVStore {
public:
    vector<vector<shared_ptr<Entity>>> getByPrint() override;
};