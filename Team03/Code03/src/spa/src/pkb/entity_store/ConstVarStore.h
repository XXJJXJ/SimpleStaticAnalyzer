#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "common/Entity.h"
#include "EntityStoreInterface.h"

using namespace std;

class ConstVarStore : public EntityStoreInterface<Entity> {
private:
    unordered_map<string, shared_ptr<Entity>> items;
public:
    ConstVarStore();
    bool add(shared_ptr<Entity> item) override;
    shared_ptr<Entity> get(const string& name) override;
    vector<shared_ptr<Entity>> getAll() const override;
    void clear() override;
    ~ConstVarStore();
};