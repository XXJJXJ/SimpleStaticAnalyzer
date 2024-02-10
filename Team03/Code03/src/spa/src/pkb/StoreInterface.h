#pragma once

using namespace std;

template <typename T>
class StoreInterface {
public:
    virtual bool add(shared_ptr<T> item) = 0;
    virtual vector<shared_ptr<T>> getAll() const = 0;
    virtual void clear() = 0;
    virtual ~StoreInterface() {}
};