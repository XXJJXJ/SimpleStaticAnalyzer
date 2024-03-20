#pragma once

#include <common/Util.h>
#include <common/Cfg.h>
#include <common/CfgNode.h>
#include <common/ArithmeticOperation.h>
#include <common/AssignStatement.h>
#include <common/CallStatement.h>
#include <common/ConditionalOperation.h>
#include <common/Constant.h>
#include <common/IfStatement.h>
#include <common/PrintStatement.h>
#include <common/Procedure.h>
#include <common/ReadStatement.h>
#include <common/RelationalOperation.h>
#include <common/Variable.h>
#include <common/WhileStatement.h>
#include "Visitor.h"

class CfgExtractor : public Visitor {
public:
	CfgExtractor(shared_ptr<Cfg> cfg);
	void visitArithmeticalOperation(shared_ptr<ArithmeticOperation> arithmeticOperation) override;
	void visitConditionalOperation(shared_ptr<ConditionalOperation> conditionalOperation) override;
	void visitRelationalOperation(shared_ptr<RelationalOperation> relationalOperation) override;
	void visitAssignStatement(shared_ptr<AssignStatement> assignStatement) override;
	void visitCallStatement(shared_ptr<CallStatement> callStatement) override;
	void visitPrintStatement(shared_ptr<PrintStatement> printStatement) override;
	void visitReadStatement(shared_ptr<ReadStatement> readStatement) override;
	void visitIfStatement(shared_ptr<IfStatement> ifStatement) override;
	void visitWhileStatement(shared_ptr<WhileStatement> whileStatement) override;
	void visitProcedure(shared_ptr<Procedure> procedure) override;
	void visitVariable(shared_ptr<Variable> variable) override;
	void visitConstant(shared_ptr<Constant> constant) override;

private:
	void processStatements(StatementListContainer& statementList);
	void addNextCfgNodeAndUpdate(shared_ptr<CfgNode> node, bool value);
	void addStatementCfgNode(shared_ptr<Statement> statement);
	shared_ptr<Cfg> cfg;
	string procedureName;
	shared_ptr<CfgNode> cfgNode;
};