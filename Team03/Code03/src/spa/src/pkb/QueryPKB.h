#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "common/expression/Constant.h"
#include "common/expression/Variable.h"
#include "common/Procedure.h"
#include "common/statement/Statement.h"
#include "common/statement/AssignStatement.h"
#include "common/statement/PrintStatement.h"
#include "common/statement/ReadStatement.h"
#include "common/statement/CallStatement.h"
#include "common/statement/IfStatement.h"
#include "common/statement/WhileStatement.h"
#include "manager/AbstractionManager.h"
#include "manager/EntityManager.h"
#include "manager/PatternManager.h"

using namespace std;

class QueryManager {
private:
    shared_ptr<AbstractionManager> am;
    shared_ptr<PatternManager> pm;
    shared_ptr<EntityManager> em;

    // For caching of procedure to variable results
    unordered_map<string, vector<vector<shared_ptr<Entity>>>> procVarResultCache;

    // Private helpers
    virtual vector<shared_ptr<Entity>> getAllConstants();
    virtual vector<shared_ptr<Entity>> getAllVariables();
    
    virtual vector<shared_ptr<Procedure>> getAllProcedures();
    virtual vector<shared_ptr<Statement>> getAllStatements();
    virtual vector<shared_ptr<AssignStatement>> getAllAssignStatements();
    virtual vector<shared_ptr<PrintStatement>> getAllPrintStatements();
    virtual vector<shared_ptr<ReadStatement>> getAllReadStatements();
    virtual vector<shared_ptr<CallStatement>> getAllCallStatements();
    virtual vector<shared_ptr<IfStatement>> getAllIfStatements();
    virtual vector<shared_ptr<WhileStatement>> getAllWhileStatements();
    virtual bool checkLayer(shared_ptr<AssignStatement> a2, shared_ptr<Variable> targetVar, vector<shared_ptr<Statement>>& nextLayer,unordered_set<shared_ptr<Statement>>& visited, unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>>& nextTMap);
    virtual bool hasNotModifiedPath(shared_ptr<AssignStatement> a1, shared_ptr<AssignStatement> a2, unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>>& nextTMap);
public:
    QueryManager ();
    // Entity Related API
    
    virtual shared_ptr<Entity> getVariableByName(string var);
    virtual vector<shared_ptr<Entity>> getAllEntitiesByType(EntityType entityType);

    // Abstraction related
    virtual vector<vector<shared_ptr<Entity>>> getFollowS();
    virtual vector<vector<shared_ptr<Entity>>> getFollowT();

    virtual vector<vector<shared_ptr<Entity>>> getParentS();
    virtual vector<vector<shared_ptr<Entity>>> getParentT();

    virtual vector<vector<shared_ptr<Entity>>> getUseByType(EntityType entType);
    virtual vector<vector<shared_ptr<Entity>>> getUseByProcedure();

    virtual vector<vector<shared_ptr<Entity>>> getModifyByType(EntityType entType);
    virtual vector<vector<shared_ptr<Entity>>> getModifyByProcedure();

    virtual vector<vector<shared_ptr<Entity>>> getCallS();
    virtual vector<vector<shared_ptr<Entity>>> getCallT();

    virtual vector<vector<shared_ptr<Entity>>> getNextS();
    virtual vector<vector<shared_ptr<Entity>>> getNextT();

    virtual vector<vector<shared_ptr<Entity>>> getAffects();

    // Pattern Related
    virtual vector<vector<shared_ptr<Entity>>> getAssignPattern(string expr, bool hasWildcard);
    // slightly different from assign pattern because if and while pattern may have multiple variables
    virtual vector<vector<shared_ptr<Entity>>> getIfPattern();
    virtual vector<vector<shared_ptr<Entity>>> getWhilePattern();
    

    virtual unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> getFollowSMap();
    virtual unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> getFollowTMap();
    virtual unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> getParentSMap();
    virtual unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> getParentTMap();
    virtual unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getUseAllMap();
    virtual unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getUseByPrintMap();
    virtual unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getModifyAllMap();
    virtual unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> getModifyByReadMap();
    virtual unordered_map<string, unordered_set<shared_ptr<Variable>>> getUseByProcedureMap();
    virtual unordered_map<string, unordered_set<shared_ptr<Variable>>> getModifyByProcedureMap();

    virtual void clear();
};

