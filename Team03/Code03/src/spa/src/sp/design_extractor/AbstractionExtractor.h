#pragma once

#include "Visitor.h"
#include "common/Util.h"
#include "common/Entity.h"
#include "common/Procedure.h"
#include "common/expression/Variable.h"
#include "common/statement/ReadStatement.h"
#include "common/statement/PrintStatement.h"
#include "common/expression/Constant.h"
#include "common/expression/ArithmeticOperation.h"
#include "common/expression/ConditionalOperation.h"
#include "common/expression/RelationalOperation.h"
#include "common/statement/CallStatement.h"
#include "pkb/PopulatePKB.h"

class AbstractionExtractor : public Visitor {
public:
    AbstractionExtractor(shared_ptr<Populator> pkb);
    void visitProcedure(shared_ptr<Procedure> procedure) override;
    void visitVariable(shared_ptr<Variable> variable) override {};
    void visitReadStatement(shared_ptr<ReadStatement> readStatement) override;
    void visitPrintStatement(shared_ptr<PrintStatement> printStatement) override;
    void visitConstant(shared_ptr<Constant> constant) override {};
    void visitArithmeticOperation(shared_ptr<ArithmeticOperation> arithmeticOperation) override {};
    void visitAssignStatement(shared_ptr<AssignStatement> assignStatement) override;
    void visitConditionalOperation(shared_ptr<ConditionalOperation> conditionalOperation) override {};
    void visitRelationalOperation(shared_ptr<RelationalOperation> relationalOperation) override {};
    void visitIfStatement(shared_ptr<IfStatement> ifStatement) override;
    void visitWhileStatement(shared_ptr<WhileStatement> whileStatement) override;
    void visitCallStatement(shared_ptr<CallStatement> callStatement) override {};

private:
    void processStatements(StatementList statementList);
    void extractFollows(StatementList statementList);
    void extractParent(StatementList statementList, shared_ptr<Statement> statement);
    void extractArgumentsForUses(shared_ptr<Expression> expression, shared_ptr<Statement> statement);
    shared_ptr<Populator> pkbPopulator;
};