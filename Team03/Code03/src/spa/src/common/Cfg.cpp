#include "Cfg.h"

void Cfg::addProcedureNode(string procedureName, shared_ptr<CfgNode> node) {
    if (procedureNodes.find(procedureName) != procedureNodes.end()) {
        throw SemanticErrorException(
            "CFG for procedure name " + 
            procedureName +
            " already exists");
    }
    else {
        procedureNodes[procedureName] = move(node);
    }
}

void Cfg::addStatementNode(shared_ptr<Statement> statement, shared_ptr<CfgNode> node) {
    if (statementNodes.find(statement) != statementNodes.end()) {
        throw SemanticErrorException(
            "Node for Statement " + 
            statement->getName() +
            " already exists");
    }
    else {
        statementNodes[statement] = move(node);
    }
}

Cfg::ProcedureNodes Cfg::getProcedureCfgRootNodes() {
    return procedureNodes;
}

Cfg::StatementNodes Cfg::getStatementToCfg() {
    return statementNodes;
}