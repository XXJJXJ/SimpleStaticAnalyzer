#include "Cfg.h"

void Cfg::addProcedureCfg(const string& procedureName, shared_ptr<CfgNode> node) {
    if (procedureCfgToCfgRootNodes.find(procedureName) != procedureCfgToCfgRootNodes.end()) {
        throw SemanticErrorException(
            "CFG with procedure name " +
            procedureName +
            " already exists");
    }

    procedureCfgToCfgRootNodes[procedureName] = move(node);
}

void Cfg::addStatementCfg(shared_ptr<Statement> statement, shared_ptr<CfgNode> node) {
    if (statementToCfgNode.find(statement) != statementToCfgNode.end()) {
        throw SemanticErrorException(
            "Statement " +
            statement->getName() +
            " is already assigned a node");
    }

    statementToCfgNode[statement] = move(node);
}

Cfg::ProcedureToCfgNodeMap Cfg::getCfgRootNodes() {
    return procedureCfgToCfgRootNodes;
}

Cfg::StatementToNodeMap Cfg::getStatementToCfg() {
    return statementToCfgNode;
}
