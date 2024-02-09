#include "common/Entity.h"
#include "Store.h"

// TODO: To be modified after finalizing PrintStatement class fields
class PrintStatementStore : public StoreInterface<PrintStatement> {
private:
    unordered_set<shared_ptr<PrintStatement>> items;
public:
    bool add(shared_ptr<PrintStatement> printStmt) override {
        items.insert(printStmt);
        return true;
    }
    vector<shared_ptr<PrintStatement>> getAll() const override {
        vector<shared_ptr<PrintStatement>> allItems;
        for (const auto& item : items) {
            allItems.push_back(item);
        }
        return allItems;
    }
    void clear() override {

    }
    ~PrintStatementStore() {
        clear();
    }
};

// TODO: To be modified after finalizing ReadStatement class fields
class ReadStatementStore : public StoreInterface<ReadStatement> {
private:
    unordered_set<shared_ptr<ReadStatement>> items;
public:
    bool add(shared_ptr<ReadStatement> readStmt) override {
        items.insert(readStmt);
        return true;
    }
    vector<shared_ptr<ReadStatement>> getAll() const override {
        vector<shared_ptr<ReadStatement>> allItems;
        for (const auto& item : items) {
            allItems.push_back(item);
        }
        return allItems;
    }
    void clear() override {

    }
    ~ReadStatementStore() override {
        clear();
    }
};