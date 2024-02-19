#pragma once

#include <set>
#include <unordered_map>
#include "abstraction_store/ModifyStore.h"
#include "abstraction_store/UseStore.h"
#include "abstraction_store/FollowStore.h"
#include "abstraction_store/ParentStore.h"

using namespace std;

class AbstractionManager {
private:
    // Private constructor to prevent external instantiation
    AbstractionManager() {}
    static shared_ptr<AbstractionManager> instance;

    ModifyStore modifyStore;
    UseStore useStore;
    FollowStore followStore;
    ParentStore parentStore;

public:
    static shared_ptr<AbstractionManager> getInstance();

    bool addFollow(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2);
    bool addParent(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2);
    bool addUses(shared_ptr<Statement> stmt, shared_ptr<Variable> var);
    bool addModifies(shared_ptr<Statement> stmt, shared_ptr<Variable> var);

    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getFollowS();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getFollowT();

    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getParentS();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getParentT();

    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getUseByAssign();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getUseByPrint(); 
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getUseByCall();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getUseByIfWhile();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getUseAll();
    unordered_map<string, set<shared_ptr<Variable>>> getUseByProcedure();

    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getModifyByAssign();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getModifyByRead();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getModifyByCall();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getModifyByIfWhile();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getModifyAll();
    unordered_map<string, set<shared_ptr<Variable>>> getModifyByProcedure();

    void clearStore();
    static void clear();
    ~AbstractionManager();
};