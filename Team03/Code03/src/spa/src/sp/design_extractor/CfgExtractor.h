#pragma once

#include <common/Util.h>
#include <common/cfg/Cfg.h>
#include <common/cfg/CfgNode.h>
#include <common/expression/ArithmeticOperation.h>
#include <common/statement/AssignStatement.h>
#include <common/statement/CallStatement.h>
#include <common/expression/ConditionalOperation.h>
#include <common/expression/Constant.h>
#include <common/statement/IfStatement.h>
#include <common/statement/PrintStatement.h>
#include <common/Procedure.h>
#include <common/statement/ReadStatement.h>
#include <common/expression/RelationalOperation.h>
#include <common/expression/Variable.h>
#include <common/statement/WhileStatement.h>
#include "Visitor.h"

class CfgExtractor : public Visitor {
public:
    CfgExtractor(shared_ptr<Cfg> cfg);
    void visitProcedure(shared_ptr<Procedure> procedure) override;
    void visitAssignStatement(shared_ptr<AssignStatement> assignStatement) override;
    void visitCallStatement(shared_ptr<CallStatement> callStatement) override;
    void visitPrintStatement(shared_ptr<PrintStatement> printStatement) override;
    void visitReadStatement(shared_ptr<ReadStatement> readStatement) override;
    void visitIfStatement(shared_ptr<IfStatement> ifStatement) override;
    void visitWhileStatement(shared_ptr<WhileStatement> whileStatement) override;
    void visitArithmeticOperation(shared_ptr<ArithmeticOperation> arithmeticOperation) override {};
    void visitConditionalOperation(shared_ptr<ConditionalOperation> conditionalOperation) override {};
    void visitConstant(shared_ptr<Constant> constant) override {};
    void visitRelationalOperation(shared_ptr<RelationalOperation> relationalOperation) override {};
    void visitVariable(shared_ptr<Variable> variable) override {};

private:
    shared_ptr<CfgNode> addNewNode();
    void processStatements(StatementList statementList);
    void addStatement(shared_ptr<Statement> statement);
    void addNextNode(bool condition, shared_ptr<CfgNode> node);
    void processIfBlocks(bool isThenBlock,
                         shared_ptr<IfStatement> ifStatement,
                         shared_ptr<CfgNode> ifNode,
                         shared_ptr<CfgNode> dummyNode);
    void processWhileBlock(shared_ptr<WhileStatement> whileStatement, shared_ptr<CfgNode> whileNode);
    string procedureName;
    shared_ptr<Cfg> cfg;
    shared_ptr<CfgNode> node;
};