#pragma once

#include <unordered_map>
#include "abstraction_store/ModifyStore.h"
#include "abstraction_store/UseStore.h"
#include "abstraction_store/FollowStore.h"
#include "abstraction_store/ParentStore.h"
#include "abstraction_store/CallStore.h"

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
    CallStore callStore;

    // Helper
    void tabulateContainerStmtVarRelation(SPVStore& store);
public:
    static shared_ptr<AbstractionManager> getInstance();

    bool addFollow(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2);
    bool addParent(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2);
    bool addUses(shared_ptr<Statement> stmt, shared_ptr<Variable> var);
    bool addModifies(shared_ptr<Statement> stmt, shared_ptr<Variable> var);
    bool addCalls(shared_ptr<Procedure> proc1, shared_ptr<Procedure> proc2);

    void tabulate();

    vector<vector<shared_ptr<Entity>>> getFollowS();
    vector<vector<shared_ptr<Entity>>> getFollowT();

    vector<vector<shared_ptr<Entity>>> getParentS();
    vector<vector<shared_ptr<Entity>>> getParentT();

    vector<vector<shared_ptr<Entity>>> getUseByType(EntityType entType);
    vector<vector<shared_ptr<Entity>>> getModifyByType(EntityType entType);

    unordered_map<string, unordered_set<shared_ptr<Variable>>> getUseByProcedureMap();
    unordered_map<string, unordered_set<shared_ptr<Variable>>> getModifyByProcedureMap();

    vector<vector<shared_ptr<Entity>>> getCallS();
    vector<vector<shared_ptr<Entity>>> getCallT();

    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> getFollowSMap();
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> getFollowTMap();
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> getParentSMap();
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> getParentTMap();
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getUseAllMap();
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getUseByPrintMap();
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getModifyAllMap();
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getModifyByReadMap();

    void clearStore();
    static void clear();
    ~AbstractionManager();
};