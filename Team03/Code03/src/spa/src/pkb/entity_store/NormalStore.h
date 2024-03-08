#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "EntityStoreInterface.h"

using namespace std;

class NormalStore : public EntityStoreInterface<Entity> {
private:
    unordered_map<string, shared_ptr<Entity>> items;
public:
    NormalStore();
    bool add(shared_ptr<Entity> item) override;
    shared_ptr<Entity> get(const string& name) override;
    vector<shared_ptr<Entity>> getAll() const override;
    void clear() override;
    ~NormalStore();
};