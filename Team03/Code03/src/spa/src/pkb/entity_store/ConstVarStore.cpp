#include "common/expression/Constant.h"
#include "common/expression/Variable.h"
#include "ConstVarStore.h"

ConstVarStore::ConstVarStore() : items() {};

bool ConstVarStore::add(shared_ptr<Entity> item) {
    items[item->getName()] = item;
    return true;
}

vector<shared_ptr<Entity>> ConstVarStore::getAll() const {
    vector<shared_ptr<Entity>> allItems;
    for (const auto& item : items) {
        allItems.push_back(item.second);
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
}


ConstVarStore::~ConstVarStore() {
    clear();
}