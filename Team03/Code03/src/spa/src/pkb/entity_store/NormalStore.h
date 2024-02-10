#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "EntityStoreInterface.h"

using namespace std;

template <typename T>
class NormalStore : public EntityStoreInterface<T> {
private:
    unordered_set<shared_ptr<T>> items;
public:
    NormalStore();
    bool add(shared_ptr<T> item) override;
    vector<shared_ptr<T>> getAll() const override;
    void clear() override;
    ~NormalStore();
};