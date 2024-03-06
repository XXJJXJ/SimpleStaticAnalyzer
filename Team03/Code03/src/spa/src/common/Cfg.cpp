#include "Cfg.h"

void Cfg::addProcedureCfg(const string& procedureName, shared_ptr<CfgNode>& node) {
    if (cfgRootNodes.find(procedureName) != cfgRootNodes.end()) {
        throw SemanticErrorException(
            "CFG with procedure name " +
            procedureName +
            " already exists");
    }

    cfgRootNodes[procedureName] = move(node);
}

void Cfg::addStatementCfg(int statementNumber, shared_ptr<CfgNode>& node) {
    if (statementToCfg.find(statementNumber) != statementToCfg.end()) {
        throw SemanticErrorException(
            "Statement " +
            to_string(statementNumber) +
            " is already assigned a node");
    }

    statementToCfg[statementNumber] = move(node);
}

Cfg::ProcedureToCfgNodeMap Cfg::getCfgRootNodes() {
    return cfgRootNodes;
}

Cfg::StatementNumberToNodeMap Cfg::getStatementToCfg() {
    return statementToCfg;
}
