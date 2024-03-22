#include "CfgExtractor.h"

CfgExtractor::CfgExtractor(shared_ptr<Cfg> cfg_) : cfg(cfg_) {}

void CfgExtractor::processStatements(StatementList statementList) {
    for (shared_ptr<Statement> statement : statementList) {
        shared_ptr<CfgExtractor> cfgExtractor = make_shared<CfgExtractor>(*this);
        statement->accept(cfgExtractor);
        procedureName = cfgExtractor->procedureName;
        cfg = cfgExtractor->cfg;
        cfgNode = cfgExtractor->cfgNode;
    }
}

void CfgExtractor::addStatementNode(shared_ptr<Statement> statement) {
    cfgNode->addStatementNode(statement);
    cfg->addStatementNode(statement, cfgNode);
}

void CfgExtractor::addNextNode(bool condition, shared_ptr<CfgNode> node) {
    cfgNode->addNextNode(condition, node);
    node->addParent(cfgNode);
    cfgNode = node;
}

void CfgExtractor::visitProcedure(shared_ptr<Procedure> procedure) {
    procedureName = procedure->getName();
    cfgNode = make_shared<CfgNode>();
    cfg->addProcedureNode(procedureName, cfgNode);
    processStatements(procedure->getStatementList());
}

void CfgExtractor::visitAssignStatement(shared_ptr<AssignStatement> assignStatement) {
    addStatementNode(assignStatement);
}

void CfgExtractor::visitCallStatement(shared_ptr<CallStatement> callStatement) {
    addStatementNode(callStatement);
}

void CfgExtractor::visitPrintStatement(shared_ptr<PrintStatement> printStatement) {
    addStatementNode(printStatement);
}

void CfgExtractor::visitReadStatement(shared_ptr<ReadStatement> readStatement) {
    addStatementNode(readStatement);
}

shared_ptr<CfgNode> CfgExtractor::addNewNode() {
    shared_ptr<CfgNode> newNode = make_shared<CfgNode>();
    if (!cfgNode->getStatementList().empty()) {
        addNextNode(true, newNode);
    }
    else {
        newNode = cfgNode;
    }
    return newNode;
}

void CfgExtractor::visitIfStatement(shared_ptr<IfStatement> ifStatement) {
    shared_ptr<CfgNode> ifNode = addNewNode();
    shared_ptr<CfgNode> dummyNode = make_shared<CfgNode>();
    addStatementNode(ifStatement);
    processIfBlocks(true, ifStatement, ifNode, dummyNode);
    processIfBlocks(false, ifStatement, ifNode, dummyNode);
}

void CfgExtractor::visitWhileStatement(shared_ptr<WhileStatement> whileStatement) {
    shared_ptr<CfgNode> whileNode = addNewNode();
    addStatementNode(whileStatement);
    processWhileBlock(whileStatement, whileNode);
}

void CfgExtractor::processIfBlocks(bool isThenBlock, shared_ptr<IfStatement> ifStatement, shared_ptr<CfgNode> IfNode, shared_ptr<CfgNode> dummyNode) {
    shared_ptr<CfgNode> blockNode = make_shared<CfgNode>();
    addNextNode(isThenBlock, blockNode);
    processStatements(isThenBlock ? ifStatement->getThenStatementList() : ifStatement->getElseStatementList());
    addNextNode(true, dummyNode);
}

void CfgExtractor::processWhileBlock(shared_ptr<WhileStatement> whileStatement, shared_ptr<CfgNode> whileNode) {
    shared_ptr<CfgNode> loopNode = make_shared<CfgNode>();
    shared_ptr<CfgNode> dummyNode = make_shared<CfgNode>();
    addNextNode(true, loopNode);
    processStatements(whileStatement->getStatementList());
    addNextNode(true, whileNode);
    addNextNode(false, dummyNode);
}