#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Entity.h"
#include "EntityManager.h"

using namespace std;

class Populator {
protected:
    EntityManager* em;
public:
    Populator();
    bool addProcedure(Procedure proc);
    bool addAssignStatement(Statement stmt);
    bool addCallStatement(Statement stmt);
    bool addPrintStatement(Statement stmt);
    bool addReadStatement(Statement stmt);
    bool addIfStatement(Statement stmt);
    bool addWhileStatement(Statement stmt);
    bool addConstant(Constant* c);
};
