#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include "common/Procedure.h"

template <typename T>
class StoreInterface {
public:
    virtual bool add(shared_ptr<T> item) = 0;
    virtual vector<shared_ptr<T>> getAll() const = 0;
    virtual void clear() = 0;
    virtual ~StoreInterface() {}
};

// For constant and variable store use
template <typename T>
class NormalStore : public StoreInterface<T> {
private:
    std::unordered_set<shared_ptr<T>> items;
public:
    NormalStore() : items() {};

    bool add(shared_ptr<T> item) override {
        items.insert(item);
        return true;
    }
    // Implementation to get all items from the store
    vector<shared_ptr<T>> getAll() const override {
        vector<shared_ptr<T>> allItems;
        for (const auto& item : items) {
            allItems.push_back(item);
        }
        return allItems;
    }
    // Implementation to clear all items from the store
    void clear() override {
        items.clear();
    }
    // Destructor to clean up items
    ~NormalStore() override {
        clear();
    }
};

class ProcedureStore : public StoreInterface<Procedure> {
private:
    std::unordered_map<string, shared_ptr<Procedure>> nameToProcMap;
public:
    bool add(shared_ptr<Procedure> procedure) override {
        // check if it exists, procedures should not have duplicate 
        if (nameToProcMap.find(procedure->getProcedureName()) != nameToProcMap.end()) {
            return false;
        }
        nameToProcMap[procedure->getProcedureName()] = procedure;
        return true;
    }

    vector<shared_ptr<Procedure>> getAll() const override {
        vector<shared_ptr<Procedure>> allProcedures;
        for (const auto& pair : nameToProcMap) {
            allProcedures.push_back(pair.second);
        }
        return allProcedures;
    }

    // getByProcName(string name)

    void clear() override {
        // clean the maps
        nameToProcMap.clear();
    }

    ~ProcedureStore() override {
        clear();
    }
};