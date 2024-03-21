#include "CfgExtractor.h"

CfgExtractor::CfgExtractor(shared_ptr<Cfg> cfg_) : cfg(cfg_) {}

void CfgExtractor::processStatements(StatementListContainer statementList) {
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

void CfgExtractor::addNextNode(shared_ptr<CfgNode> node, bool condition) {
    cfgNode->addNextNode(condition, node);
    node->addParent(cfgNode);
    cfgNode = node;
}

void CfgExtractor::visitProcedure(shared_ptr<Procedure> procedure) {
    string procedureName_ = procedure->getName();
    procedureName = procedureName_;
    cfgNode = make_shared<CfgNode>();
    cfg->addProcedureNode(procedureName, cfgNode);
    auto statements = procedure->getStatementList();
    processStatements(statements);
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

void CfgExtractor::visitIfStatement(shared_ptr<IfStatement> ifStatement) {
    auto ifNode = make_shared<CfgNode>();
    auto thenNode = make_shared<CfgNode>();
    auto elseNode = make_shared<CfgNode>();
    auto dummyNode = make_shared<CfgNode>();

    if (cfgNode->getStatementList().size() > 0) {
        addNextNode(ifNode, true);
    }
    else {
        ifNode = cfgNode;
    }

    addStatementNode(ifStatement);

    StatementListContainer thenStatementList = ifStatement->getThenStatementList();
    StatementListContainer elseStatementList = ifStatement->getElseStatementList();

    //Construct CFG for then block (If statement's condition evaluates to true)
    addNextNode(thenNode, true);
    processStatements(thenStatementList);

    //Connect CFG at the end of then block to dummy node
    addNextNode(dummyNode, true);

    //Construct CFG for else block (If statement's condition evaluates to false)
    cfgNode = ifNode;
    addNextNode(elseNode, false);
    processStatements(elseStatementList);

    //Connect CFG at the end of else block to dummy node
    addNextNode(dummyNode, true);
}

void CfgExtractor::visitWhileStatement(shared_ptr<WhileStatement> whileStatement) {
    auto whileNode = make_shared<CfgNode>();
    auto loopNode = make_shared<CfgNode>();
    auto dummyNode = make_shared<CfgNode>();

    if (cfgNode->getStatementList().size() > 0) {
        addNextNode(whileNode, true);
    }
    else {
        whileNode = cfgNode;
    }

    addStatementNode(whileStatement);
    auto statementList = whileStatement->getStatementList();

    //Construct CFG for while block (While statement's condition evaluates to true)
    addNextNode(loopNode, true);
    processStatements(statementList);

    //Connect CFG at the end of while block to start of while block (While statement's condition still evaluates to true)
    addNextNode(whileNode, true);

    //Connect CFG at the end of while block to dummy node (While statement's condition evaluates to false)
    addNextNode(dummyNode, false);
}

void CfgExtractor::visitArithmeticalOperation(shared_ptr<ArithmeticOperation> arithmeticOperation) {}
void CfgExtractor::visitConditionalOperation(shared_ptr<ConditionalOperation> conditionalOperation) {}
void CfgExtractor::visitConstant(shared_ptr<Constant> constant) {}
void CfgExtractor::visitRelationalOperation(shared_ptr<RelationalOperation> relationalOperation) {}
void CfgExtractor::visitVariable(shared_ptr<Variable> variable) {}