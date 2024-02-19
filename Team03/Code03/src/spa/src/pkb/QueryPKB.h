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
public:
    QueryManager ();
    // Entity Related API
    virtual vector<shared_ptr<Constant>> getAllConstants();
    virtual vector<shared_ptr<Variable>> getAllVariables();
    virtual vector<shared_ptr<Procedure>> getAllProcedures();
    virtual vector<shared_ptr<Statement>> getAllStatements();
    virtual vector<shared_ptr<AssignStatement>> getAllAssignStatements();
    virtual vector<shared_ptr<PrintStatement>> getAllPrintStatements();
    virtual vector<shared_ptr<ReadStatement>> getAllReadStatements();
    virtual vector<shared_ptr<CallStatement>> getAllCallStatements();
    virtual vector<shared_ptr<IfStatement>> getAllIfStatements();
    virtual vector<shared_ptr<WhileStatement>> getAllWhileStatements();

    // Abstraction related API
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getFollowS();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getFollowT();

    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getParentS();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getParentT();

    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getUseByAssign();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getUseByPrint(); 
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getUseByCall();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getUseByIfWhile();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getUseAll();
    virtual unordered_map<string, set<shared_ptr<Variable>>> getUseByProcedure();

    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getModifyByAssign();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getModifyByRead();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getModifyByCall();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getModifyByIfWhile();
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> getModifyAll();
    virtual unordered_map<string, set<shared_ptr<Variable>>> getModifyByProcedure();

    // Pattern related API
    virtual vector<shared_ptr<AssignStatement>> getAssignPattern(string targetVariable, string exprString, shared_ptr<Expression> expr, bool hasWildcard);

    // For testing purposes
    virtual void clear();
};

