#include "CfgExtractor.h"

CfgExtractor::CfgExtractor(shared_ptr<Cfg> cfg_) : cfg(cfg_) {}

void CfgExtractor::processStatements(StatementList statementList) {
    for (shared_ptr<Statement> statement : statementList) {
        shared_ptr<CfgExtractor> cfgExtractor = make_shared<CfgExtractor>(*this);
        statement->accept(cfgExtractor);
        procedureName = cfgExtractor->procedureName;
        cfg = cfgExtractor->cfg;
        node = cfgExtractor->node;
    }
}

void CfgExtractor::addStatement(shared_ptr<Statement> statement) {
    node->addStatement(statement);
    cfg->addStatementNode(statement, node);
}

void CfgExtractor::addNextNode(bool condition, shared_ptr<CfgNode> nextNode) {
    nextNode->addParentNode(node);
    node->addNextNode(condition, nextNode);
    node = nextNode;
}

void CfgExtractor::visitProcedure(shared_ptr<Procedure> procedure) {
    procedureName = procedure->getName();
    node = make_shared<CfgNode>();
    cfg->addProcedureNode(procedureName, node);
    processStatements(procedure->getStatementList());
}

shared_ptr<CfgNode> CfgExtractor::addNewNode() {
    shared_ptr<CfgNode> newNode = make_shared<CfgNode>();
    if (!node->getStatementList().empty()) {
        addNextNode(true, newNode);
    }
    else {
        newNode = node;
    }
    return newNode;
}

void CfgExtractor::visitIfStatement(shared_ptr<IfStatement> ifStatement) {
    shared_ptr<CfgNode> ifNode = addNewNode();
    shared_ptr<CfgNode> dummyNode = make_shared<CfgNode>();
    addStatement(ifStatement);
    processIfBlocks(true, ifStatement, ifNode, dummyNode);
    processIfBlocks(false, ifStatement, ifNode, dummyNode);
}

void CfgExtractor::visitWhileStatement(shared_ptr<WhileStatement> whileStatement) {
    shared_ptr<CfgNode> whileNode = addNewNode();
    addStatement(whileStatement);
    processWhileBlock(whileStatement, whileNode);
}

void CfgExtractor::processIfBlocks(bool isThenBlock, shared_ptr<IfStatement> ifStatement, shared_ptr<CfgNode> ifNode, shared_ptr<CfgNode> dummyNode) {
    shared_ptr<CfgNode> blockNode = make_shared<CfgNode>();
    addNextNode(isThenBlock, blockNode);
    processStatements(isThenBlock ? ifStatement->getThenStatementList() : ifStatement->getElseStatementList());
    addNextNode(true, dummyNode);
    if (isThenBlock) {
        node = ifNode; 
    }
}

void CfgExtractor::processWhileBlock(shared_ptr<WhileStatement> whileStatement, shared_ptr<CfgNode> whileNode) {
    shared_ptr<CfgNode> loopNode = make_shared<CfgNode>();
    shared_ptr<CfgNode> dummyNode = make_shared<CfgNode>();
    addNextNode(true, loopNode);
    processStatements(whileStatement->getStatementList());
    addNextNode(true, whileNode);
    addNextNode(false, dummyNode);
}

void CfgExtractor::visitAssignStatement(shared_ptr<AssignStatement> assignStatement) {
    addStatement(assignStatement);
}

void CfgExtractor::visitCallStatement(shared_ptr<CallStatement> callStatement) {
    addStatement(callStatement);
}

void CfgExtractor::visitPrintStatement(shared_ptr<PrintStatement> printStatement) {
    addStatement(printStatement);
}

void CfgExtractor::visitReadStatement(shared_ptr<ReadStatement> readStatement) {
    addStatement(readStatement);
}