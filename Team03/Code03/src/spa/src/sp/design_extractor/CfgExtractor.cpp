#include "CfgExtractor.h"

CfgExtractor::CfgExtractor(shared_ptr<Cfg> cfg_) : cfg(cfg_) {}

void CfgExtractor::visitProcedure(shared_ptr<Procedure> procedure) {
    string procedureName_ = procedure->getName();
    procedureName = procedureName_;
    cfgNode = make_shared<CfgNode>();
    cfg->addProcedureCfg(procedureName, cfgNode);
    processStatements(procedure->getStatementList());
}

void CfgExtractor::visitAssignStatement(shared_ptr<AssignStatement> assignStatement) {
    int statementNumber = assignStatement->getStatementNumber();
    addStatementCfgNode(statementNumber);
}

void CfgExtractor::visitCallStatement(shared_ptr<CallStatement> callStatement) {
    int statementNumber = callStatement->getStatementNumber();
    addStatementCfgNode(statementNumber);
}

void CfgExtractor::visitPrintStatement(shared_ptr<PrintStatement> printStatement) {
    int statementNumber = printStatement->getStatementNumber();
    addStatementCfgNode(statementNumber);
}

void CfgExtractor::visitReadStatement(shared_ptr<ReadStatement> readStatement) {
    int statementNumber = readStatement->getStatementNumber();
    addStatementCfgNode(statementNumber);
}

void CfgExtractor::visitIfStatement(shared_ptr<IfStatement> ifStatement) {
    int statementNumber = ifStatement->getStatementNumber();
    auto ifCfgNode = make_shared<CfgNode>();
    auto thenCfgNode = make_shared<CfgNode>();
    auto elseCfgNode = make_shared<CfgNode>();
    auto dummyCfgNode = make_shared<CfgNode>();

    if (cfgNode->getStatementNumbers().size() > 0) {
        addNextCfgNodeAndUpdate(ifCfgNode, true);
    }
    else {
        ifCfgNode = cfgNode;
    }

    addStatementCfgNode(statementNumber);

    auto thenStatementList = ifStatement->getThenStatementList();
    auto elseStatementList = ifStatement->getElseStatementList();

    //Construct CFG for then block (If statement's condition evaluates to true)
    addNextCfgNodeAndUpdate(thenCfgNode, true);
    processStatements(thenStatementList);

    //Connect CFG at the end of then block to dummy node
    addNextCfgNodeAndUpdate(dummyCfgNode, true);

    //Construct CFG for else block (If statement's condition evaluates to false)
    cfgNode = ifCfgNode;
    addNextCfgNodeAndUpdate(elseCfgNode, false);
    processStatements(elseStatementList);

    //Connect CFG at the end of else block to dummy node
    addNextCfgNodeAndUpdate(dummyCfgNode, true);
}

void CfgExtractor::visitWhileStatement(shared_ptr<WhileStatement> whileStatement) {
    int statementNumber = whileStatement->getStatementNumber();
    auto whileCfgNode = make_shared<CfgNode>();
    auto loopCfgNode = make_shared<CfgNode>();
    auto dummyCfgNode = make_shared<CfgNode>();

    if (cfgNode->getStatementNumbers().size() > 0) {
        addNextCfgNodeAndUpdate(whileCfgNode, true);
    }
    else {
        whileCfgNode = cfgNode;
    }

    addStatementCfgNode(statementNumber);
    auto statementList = whileStatement->getStatementList();

    //Construct CFG for while block (While statement's condition evaluates to true)
    addNextCfgNodeAndUpdate(loopCfgNode, true);
    processStatements(statementList);

    //Connect CFG at the end of while block to start of while block (While statement's condition still evaluates to true)
    addNextCfgNodeAndUpdate(whileCfgNode, true);

    //Connect CFG at the end of while block to dummy node (While statement's condition evaluates to false)
    addNextCfgNodeAndUpdate(dummyCfgNode, false);
}

void CfgExtractor::processStatements(StatementListContainer& statementList) {
    for (auto const& statement : statementList) {
        auto cfgExtractor = make_shared<CfgExtractor>(*this);
        statement->accept(cfgExtractor);
        cfgNode = cfgExtractor->cfgNode;
        cfg = cfgExtractor->cfg;
        procedureName = cfgExtractor->procedureName;
    }
}

void CfgExtractor::addStatementCfgNode(int statementNumber) {
    cfgNode->addStatement(statementNumber);
    cfg->addStatementCfg(statementNumber, cfgNode);
}

void CfgExtractor::addNextCfgNodeAndUpdate(shared_ptr<CfgNode> node, bool value) {
    cfgNode->addNextNode(value, node);
    node->addParent(cfgNode);
    cfgNode = node;
}

void CfgExtractor::visitArithmeticalOperation(shared_ptr<ArithmeticOperation> arithmeticOeration) {}

void CfgExtractor::visitConditionalOperation(shared_ptr<ConditionalOperation> conditionalOperation) {}

void CfgExtractor::visitRelationalOperation(shared_ptr<RelationalOperation> relationalOperation) {}

void CfgExtractor::visitVariable(shared_ptr<Variable> variable) {}

void CfgExtractor::visitConstant(shared_ptr<Constant> constant) {}