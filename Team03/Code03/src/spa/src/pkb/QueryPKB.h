#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "common/Variable.h"
#include "common/Procedure.h"
#include "common/Statement.h"
#include "common/PrintStatement.h"
#include "common/ReadStatement.h"
#include "EntityManager.h"

using namespace std;

// virtual vector<Statement> getAssignStatements() = 0;
// virtual vector<Statement> getCallStatements() = 0;
// virtual vector<Statement> getIfStatements() = 0;
// virtual vector<Statement> getWhileStatements() = 0;

class QueryMananger {
private:
    EntityManager* em;
public:
    QueryMananger ();
    // vector<shared_ptr<Constant>> getAllConstants();
    vector<shared_ptr<Variable>> getAllVariables();
    vector<shared_ptr<Procedure>> getAllProcedures();
    vector<shared_ptr<PrintStatement>> getAllPrintStatements();
    vector<shared_ptr<ReadStatement>> getAllReadStatements();
    vector<shared_ptr<Statement>> getAllStatements();
    // vector<Statement> getAllStatements() = 0;
};