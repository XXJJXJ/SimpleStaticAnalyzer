#pragma once

#include "Visitor.h"
#include "common/Util.h"
#include "common/Operation.h"
#include "common/Procedure.h"
#include "common/Variable.h"
#include "common/ReadStatement.h"
#include "common/PrintStatement.h"
#include "common/Constant.h"
#include "common/ArithmeticOperation.h"
#include "common/ConditionalOperation.h"
#include "common/RelationalOperation.h"
#include "pkb/PopulatePKB.h"

class EntityExtractor : public Visitor {
public:
	EntityExtractor(shared_ptr<Populator> pkb);
	void visitProcedure(shared_ptr<Procedure> procedure) override;
	void visitVariable(shared_ptr<Variable> variable) override;
	void visitReadStatement(shared_ptr<ReadStatement> readStatement) override;
	void visitPrintStatement(shared_ptr<PrintStatement> printStatement) override;
	void visitConstant(shared_ptr<Constant> constant) override;
	void visitArithmeticalOperation(shared_ptr<ArithmeticOperation> arithmeticOperation) override;
	void visitAssignStatement(shared_ptr<AssignStatement> assignStatement) override;
	void visitConditionalOperation(shared_ptr<ConditionalOperation> conditionalOperation) override;
	void visitRelationalOperation(shared_ptr<RelationalOperation> relationalOperation) override;
	void visitIfStatement(shared_ptr<IfStatement> ifStatement) override;
	void visitWhileStatement(shared_ptr<WhileStatement> whileStatement) override;
	void visitCallStatement(shared_ptr<CallStatement> callStatement) override;

private:
	void processStatements(StatementListContainer statementList);
	void extractArgs(optional<PairOfArguments> arguments);
	shared_ptr<Populator> pkbPopulator;
};