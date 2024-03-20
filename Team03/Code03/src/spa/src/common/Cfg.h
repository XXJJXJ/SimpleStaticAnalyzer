#pragma once

#include "CfgNode.h"
#include "spa_exception/SemanticErrorException.h"

class Cfg {
public:
    typedef unordered_map<string, shared_ptr<CfgNode>> ProcedureToCfgNodeMap;
    typedef unordered_map<shared_ptr<Statement>, shared_ptr<CfgNode>> StatementToNodeMap; 
    void addProcedureCfg(const string& procedureName, shared_ptr<CfgNode> node);
    void addStatementCfg(shared_ptr<Statement> statement, shared_ptr<CfgNode> node);
    ProcedureToCfgNodeMap getCfgRootNodes();
    StatementToNodeMap getStatementToCfg();

private:
    ProcedureToCfgNodeMap procedureCfgToCfgRootNodes;
    StatementToNodeMap statementToCfgNode;
};