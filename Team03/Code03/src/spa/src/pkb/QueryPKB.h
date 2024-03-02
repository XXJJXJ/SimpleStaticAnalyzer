#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "common/Constant.h"
#include "common/Variable.h"
#include "common/Procedure.h"
#include "common/Statement.h"
#include "common/AssignStatement.h"
#include "common/PrintStatement.h"
#include "common/ReadStatement.h"
#include "common/CallStatement.h"
#include "common/IfStatement.h"
#include "common/WhileStatement.h"
#include "AbstractionManager.h"
#include "EntityManager.h"
#include "PatternManager.h"

using namespace std;

class QueryManager {
private:
    shared_ptr<AbstractionManager> am;
    shared_ptr<PatternManager> pm;
    shared_ptr<EntityManager> em;

    // For caching of procedure to variable results
    unordered_map<string, vector<vector<shared_ptr<Entity>>>> procVarResultCache;
public:
    QueryManager ();
    // Entity Related API
    virtual vector<shared_ptr<Entity>> getAllConstants();
    virtual vector<shared_ptr<Entity>> getAllVariables();
    virtual shared_ptr<Entity> getVariableByName(string var);
    virtual vector<shared_ptr<Procedure>> getAllProcedures();
    virtual vector<shared_ptr<Statement>> getAllStatements();
    virtual vector<shared_ptr<AssignStatement>> getAllAssignStatements();
    virtual vector<shared_ptr<PrintStatement>> getAllPrintStatements();
    virtual vector<shared_ptr<ReadStatement>> getAllReadStatements();
    virtual vector<shared_ptr<CallStatement>> getAllCallStatements();
    virtual vector<shared_ptr<IfStatement>> getAllIfStatements();
    virtual vector<shared_ptr<WhileStatement>> getAllWhileStatements();
    
    virtual vector<shared_ptr<Entity>> getAllEntitiesByType(EntityType entityType);

    // Abstraction related
    virtual vector<vector<shared_ptr<Entity>>> getFollowS();
    virtual vector<vector<shared_ptr<Entity>>> getFollowT();

    virtual vector<vector<shared_ptr<Entity>>> getParentS();
    virtual vector<vector<shared_ptr<Entity>>> getParentT();

    virtual vector<vector<shared_ptr<Entity>>> getUseByAssign();
    virtual vector<vector<shared_ptr<Entity>>> getUseByPrint(); 
    virtual vector<vector<shared_ptr<Entity>>> getUseByCall();
    virtual vector<vector<shared_ptr<Entity>>> getUseByIfWhile();
    virtual vector<vector<shared_ptr<Entity>>> getUseAll();
    virtual vector<vector<shared_ptr<Entity>>> getUseByProcedure();

    virtual vector<vector<shared_ptr<Entity>>> getModifyByAssign();
    virtual vector<vector<shared_ptr<Entity>>> getModifyByRead();
    virtual vector<vector<shared_ptr<Entity>>> getModifyByCall();
    virtual vector<vector<shared_ptr<Entity>>> getModifyByIfWhile();
    virtual vector<vector<shared_ptr<Entity>>> getModifyAll();
    virtual vector<vector<shared_ptr<Entity>>> getModifyByProcedure();

    // Pattern Related
    virtual vector<shared_ptr<AssignStatement>> getAssignPattern(string targetVariable, string expr, bool hasWildcard);

    // For testing purposes
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

