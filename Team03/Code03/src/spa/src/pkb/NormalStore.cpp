#include "common/Variable.h"
#include "NormalStore.h"

template <typename T>
NormalStore<T>::NormalStore() : items() {};

template <typename T>
bool NormalStore<T>::add(shared_ptr<T> item) {
    items.insert(item);
    return true;
}

template <typename T>
vector<shared_ptr<T>> NormalStore<T>::getAll() const {
    vector<shared_ptr<T>> allItems;
    for (const auto& item : items) {
        allItems.push_back(item);
    }
    return allItems;
}

template <typename T>
void NormalStore<T>::clear() {
    items.clear();
}

template <typename T>
NormalStore<T>::~NormalStore() {
    clear();
}

template class NormalStore<Variable>;
// template class NormalStore<float>;