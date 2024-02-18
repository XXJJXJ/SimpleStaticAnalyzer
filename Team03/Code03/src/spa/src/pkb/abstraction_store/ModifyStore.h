#pragma once

#include "SPVStore.h"

class ModifyStore : public SPVStore {
public:
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getByPrint() override;
};