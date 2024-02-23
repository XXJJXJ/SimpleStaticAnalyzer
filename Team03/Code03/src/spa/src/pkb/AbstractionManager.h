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

    vector<vector<shared_ptr<Entity>>> getFollowS();
    vector<vector<shared_ptr<Entity>>> getFollowT();

    vector<vector<shared_ptr<Entity>>> getParentS();
    vector<vector<shared_ptr<Entity>>> getParentT();

    vector<vector<shared_ptr<Entity>>> getUseByAssign();
    vector<vector<shared_ptr<Entity>>> getUseByPrint(); 
    vector<vector<shared_ptr<Entity>>> getUseByCall();
    vector<vector<shared_ptr<Entity>>> getUseByIfWhile();
    vector<vector<shared_ptr<Entity>>> getUseAll();
    unordered_map<string, set<shared_ptr<Variable>>> getUseByProcedure();

    vector<vector<shared_ptr<Entity>>> getModifyByAssign();
    vector<vector<shared_ptr<Entity>>> getModifyByRead();
    vector<vector<shared_ptr<Entity>>> getModifyByCall();
    vector<vector<shared_ptr<Entity>>> getModifyByIfWhile();
    vector<vector<shared_ptr<Entity>>> getModifyAll();
    unordered_map<string, set<shared_ptr<Variable>>> getModifyByProcedure();


    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getFollowSMap();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getFollowTMap();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getParentSMap();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getParentTMap();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getUseAllMap();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getUseByPrintMap();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getModifyAllMap();
    unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getModifyByReadMap();

    void clearStore();
    static void clear();
    ~AbstractionManager();
};