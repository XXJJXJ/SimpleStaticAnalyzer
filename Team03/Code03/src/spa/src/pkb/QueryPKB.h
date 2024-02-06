#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Entity.h"
#include "EntityManager.h"

using namespace std;

// virtual vector<string> getAllVariables() = 0;
// virtual vector<Statement> getAllStatements() = 0;
// virtual vector<string> getAllProcedure() = 0;

// virtual vector<Statement> getAssignStatements() = 0;
// virtual vector<Statement> getCallStatements() = 0;
// virtual vector<Statement> getReadStatements() = 0;
// virtual vector<Statement> getPrintStatements() = 0;
// virtual vector<Statement> getIfStatements() = 0;
// virtual vector<Statement> getWhileStatements() = 0;

class QueryMananger {
protected:
    EntityManager* em;
public:
    QueryMananger ();
    vector<Constant*> getAllConstants() ;
};