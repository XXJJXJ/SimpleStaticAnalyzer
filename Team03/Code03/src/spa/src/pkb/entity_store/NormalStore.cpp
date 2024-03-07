#include "common/Constant.h"
#include "common/Variable.h"
#include "NormalStore.h"

NormalStore::NormalStore() : items() {};

bool NormalStore::add(shared_ptr<Entity> item) {
    items[item->getName()] = item;
    return true;
}

vector<shared_ptr<Entity>> NormalStore::getAll() const {
    vector<shared_ptr<Entity>> allItems;
    for (const auto& item : items) {
        allItems.push_back(item.second);
    }
    return allItems;
}

shared_ptr<Entity> NormalStore::get(const string& name) {
    if (items.find(name) != items.end()) {
        return items[name];
    }
    return nullptr;
}

void NormalStore::clear() {
    items.clear();
}


NormalStore::~NormalStore() {
    clear();
}