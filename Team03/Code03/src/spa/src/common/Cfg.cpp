#include "Cfg.h"

void Cfg::addProcedureCfg(const string& procedureName, shared_ptr<CfgNode>& node) {
    if (procedureCfgToCfgRootNodes.find(procedureName) != procedureCfgToCfgRootNodes.end()) {
        throw SemanticErrorException(
            "CFG with procedure name " +
            procedureName +
            " already exists");
    }

    procedureCfgToCfgRootNodes[procedureName] = move(node);
}

void Cfg::addStatementCfg(int statementNumber, shared_ptr<CfgNode>& node) {
    if (statementNumberToCfgNode.find(statementNumber) != statementNumberToCfgNode.end()) {
        throw SemanticErrorException(
            "Statement " +
            to_string(statementNumber) +
            " is already assigned a node");
    }

    statementNumberToCfgNode[statementNumber] = move(node);
}

Cfg::ProcedureToCfgNodeMap Cfg::getCfgRootNodes() {
    return procedureCfgToCfgRootNodes;
}

Cfg::StatementNumberToNodeMap Cfg::getStatementToCfg() {
    return statementNumberToCfgNode;
}
