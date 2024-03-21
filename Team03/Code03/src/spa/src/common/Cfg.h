#pragma once

#include "CfgNode.h"
#include "spa_exception/SemanticErrorException.h"

class Cfg {
public:
    typedef unordered_map<string, shared_ptr<CfgNode>> ProcedureNodes;
    typedef unordered_map<shared_ptr<Statement>, shared_ptr<CfgNode>> StatementNodes; 
    void addProcedureNode(string procedureName, shared_ptr<CfgNode> node);
    void addStatementNode(shared_ptr<Statement> statement, shared_ptr<CfgNode> node);
    ProcedureNodes getProcedureCfgRootNodes();
    StatementNodes getStatementToCfg();

private:
    ProcedureNodes procedureNodes;
    StatementNodes statementNodes;
};