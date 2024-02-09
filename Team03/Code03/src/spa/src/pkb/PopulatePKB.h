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
protected:
    EntityManager* em;
public:
    Populator();
    bool addProcedure(Procedure proc);
    bool addPrintStatement(PrintStatement stmt);
    bool addReadStatement(ReadStatement stmt);

    // bool addAssignStatement(Statement stmt);
    // bool addCallStatement(Statement stmt);
    // bool addIfStatement(Statement stmt);
    // bool addWhileStatement(Statement stmt);
    // bool addConstant(Constant* c);
};
