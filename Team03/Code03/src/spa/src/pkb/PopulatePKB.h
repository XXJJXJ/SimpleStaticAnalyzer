#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "common/ReadStatement.h"
#include "common/PrintStatement.h"
#include "common/Procedure.h"
#include "EntityManager.h"

using namespace std;

class Populator {
private:
    EntityManager* em;
public:
    Populator();
    // bool addConstant(shared_ptr<Constant>  c);
    bool addVariable(shared_ptr<Variable>  var);
    bool addProcedure(shared_ptr<Procedure> proc);
    bool addPrintStatement(shared_ptr<PrintStatement> stmt);
    bool addReadStatement(shared_ptr<ReadStatement> stmt);
    // bool addAssignStatement(shared_ptr<AssignStatement> stmt);
    // bool addCallStatement(shared_ptr<CallStatement> stmt);
    // bool addIfStatement(shared_ptr<IfStatement> stmt);
    // bool addWhileStatement(shared_ptr<WhileStatement> stmt);
};
