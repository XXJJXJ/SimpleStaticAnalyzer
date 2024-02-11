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
#include "EntityManager.h"

using namespace std;

class QueryManager {
private:
    EntityManager* em;
public:
    QueryManager ();
    vector<shared_ptr<Constant>> getAllConstants();
    vector<shared_ptr<Variable>> getAllVariables();
    vector<shared_ptr<Procedure>> getAllProcedures();
    vector<shared_ptr<Statement>> getAllStatements();
    vector<shared_ptr<AssignStatement>> getAllAssignStatements();
    vector<shared_ptr<PrintStatement>> getAllPrintStatements();
    vector<shared_ptr<ReadStatement>> getAllReadStatements();
    vector<shared_ptr<CallStatement>> getAllCallStatements();
    vector<shared_ptr<IfStatement>> getAllIfStatements();
    vector<shared_ptr<WhileStatement>> getAllWhileStatements();
};
