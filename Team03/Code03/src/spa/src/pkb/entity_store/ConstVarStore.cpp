#include "common/Constant.h"
#include "common/Variable.h"
#include "ConstVarStore.h"

ConstVarStore::ConstVarStore() : items() {};

bool ConstVarStore::add(shared_ptr<Entity> item) {
    items[item->getName()] = item;
    return true;
}

vector<shared_ptr<Entity>> ConstVarStore::getAll() {
    if (allItems.size() != items.size()) {  // some unit tests modifies and queries midway
        allItems.clear();
        for (const auto& item : items) {
            allItems.push_back(item.second);
        }
    }
    return allItems;
}

shared_ptr<Entity> ConstVarStore::get(const string& name) {
    if (items.find(name) != items.end()) {
        return items[name];
    }
    return nullptr;
}

void ConstVarStore::clear() {
    items.clear();
    allItems.clear();
}


ConstVarStore::~ConstVarStore() {
    clear();
}