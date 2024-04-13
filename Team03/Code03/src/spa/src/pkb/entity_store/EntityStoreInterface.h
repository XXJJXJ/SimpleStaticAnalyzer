#pragma once

using namespace std;

template <typename T>
class EntityStoreInterface {
public:
    virtual bool add(shared_ptr<T> item) = 0;
    virtual vector<shared_ptr<T>> getAll() = 0;
    virtual shared_ptr<T> get(const string& name) = 0;
    virtual void clear() = 0;
    virtual ~EntityStoreInterface() {};
};