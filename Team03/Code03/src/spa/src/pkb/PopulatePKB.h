#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "common/ReadStatement.h"
#include "common/PrintStatement.h"
#include "common/Procedure.h"
#include "AbstractionManager.h"
#include "EntityManager.h"
#include "PatternManager.h"

using namespace std;

class Populator {
private:
    shared_ptr<EntityManager> em;
    shared_ptr<AbstractionManager> am;
    shared_ptr<PatternManager> pm;
public:
    Populator();
    bool addConstant(shared_ptr<Constant>  c);
    bool addVariable(shared_ptr<Variable>  var);
    bool addProcedure(shared_ptr<Procedure> proc);
    bool addPrintStatement(shared_ptr<PrintStatement> stmt);
    bool addReadStatement(shared_ptr<ReadStatement> stmt);
    bool addAssignStatement(shared_ptr<AssignStatement> stmt);
    bool addCallStatement(shared_ptr<CallStatement> stmt);
    bool addIfStatement(shared_ptr<IfStatement> stmt);
    bool addWhileStatement(shared_ptr<WhileStatement> stmt);

    bool addFollow(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2);
    bool addParent(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2);
    bool addUses(shared_ptr<Statement> stmt, shared_ptr<Variable> var);
    bool addModifies(shared_ptr<Statement> stmt, shared_ptr<Variable> var);

    void tabulateUses();
    void tabulateModifies();

    void clear();
};
