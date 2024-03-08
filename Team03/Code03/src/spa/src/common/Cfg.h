#pragma once

#include "CfgNode.h"
#include "spa_exception/SemanticErrorException.h"

class Cfg {
public:
    typedef unordered_map<string, shared_ptr<CfgNode>> ProcedureToCfgNodeMap;
    typedef unordered_map<int, shared_ptr<CfgNode>> StatementNumberToNodeMap; 
    void addProcedureCfg(const string& procedureName, shared_ptr<CfgNode>& node);
    void addStatementCfg(int statementNumber, shared_ptr<CfgNode>& node);
    ProcedureToCfgNodeMap getCfgRootNodes();
    StatementNumberToNodeMap getStatementToCfg();

private:
    ProcedureToCfgNodeMap procedureCfgToCfgRootNodes;
    StatementNumberToNodeMap statementNumberToCfgNode;
};