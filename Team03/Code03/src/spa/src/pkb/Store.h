#pragma once

#include <string>
#include <vector>

// Generic Store Interface
template <typename T>
class StoreInterface {
public:
    // Pure virtual method to add an item to the store
    virtual void add(T* item) = 0;
    // Pure virtual method to get an item from the store by key
    virtual std::vector<T*> getAll() const = 0;
    // Pure virtual method to clear all items from the store
    virtual void clear() = 0;
    // Virtual destructor to ensure proper cleanup
    virtual ~StoreInterface() {}
};

template <typename T>
class Store : public StoreInterface<T> {
private:
    std::set<T*> items;
public:
    Store() : items() {};
    // Implementation of the pure virtual method to add an item to the store
    void add(T* item) override {
        items.insert(item);
    }
    // Implementation of the pure virtual method to get all items from the store
    std::vector<T*> getAll() const override {
        std::vector<T*> allItems;
        for (const auto& item : items) {
            allItems.push_back(item);
        }
        return allItems;
    }
    // Implementation of the pure virtual method to clear all items from the store
    void clear() override {
        for (auto& item : items) {
            delete item;
        }
        items.clear();
    }
    // Destructor to clean up items
    ~Store() {
        clear();
    }
};

