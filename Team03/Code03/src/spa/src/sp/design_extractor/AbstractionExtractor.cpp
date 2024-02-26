#include "AbstractionExtractor.h"

AbstractionExtractor::AbstractionExtractor(shared_ptr<Populator> pkb) {
	pkbPopulator = pkb;
}

void AbstractionExtractor::processStatements(StatementListContainer statementList) {
	for (auto s : statementList) {
		s->accept(make_shared<AbstractionExtractor>(*this));
	}
}

void AbstractionExtractor::extractFollows(StatementListContainer statementList) {
	for (size_t i = 0; i < statementList.size() - 1; ++i) {
		pkbPopulator->addFollow(statementList[i], statementList[i + 1]);
	}
}

void AbstractionExtractor::extractParent(StatementListContainer statementList, shared_ptr<Statement> parent) {
	for (auto s : statementList) {
		pkbPopulator->addParent(parent, s);
	}
}

void AbstractionExtractor::extractArgumentsForUses(shared_ptr<Expression> expression, shared_ptr<AssignStatement> assignStatement) {
	if (expression->isLeafNodeExpression()) {
		if (expression->getExpressionType() == EntityType::Variable) {
			pkbPopulator->addUses(assignStatement, dynamic_pointer_cast<Variable>(expression));
		}
	}
	else {
		auto arguments = expression->getArguments();
		auto& [lhs, rhs] = *arguments;
		if (lhs) {
			extractArgumentsForUses(lhs, assignStatement);
		}
		if (rhs) {
			extractArgumentsForUses(rhs, assignStatement);
		}
	}
}

void AbstractionExtractor::visitProcedure(shared_ptr<Procedure> procedure) {
	extractFollows(procedure->getStatementList());
	processStatements(procedure->getStatementList());
}

void AbstractionExtractor::visitReadStatement(shared_ptr<ReadStatement> readStatement) {
	pkbPopulator->addModifies(readStatement, readStatement->getVariable());
}

void AbstractionExtractor::visitPrintStatement(shared_ptr<PrintStatement> printStatement) {
	pkbPopulator->addUses(printStatement, printStatement->getVariable());
}

void AbstractionExtractor::visitAssignStatement(shared_ptr<AssignStatement> assignStatement) {
	extractArgumentsForUses(assignStatement->getExpression(), assignStatement);
	pkbPopulator->addModifies(assignStatement, assignStatement->getVariable());
}

void AbstractionExtractor::visitIfStatement(shared_ptr<IfStatement> ifStatement) {
	extractParent(ifStatement->getThenStatementList(), ifStatement);
	extractParent(ifStatement->getElseStatementList(), ifStatement);
	extractFollows(ifStatement->getThenStatementList());
	processStatements(ifStatement->getThenStatementList());
	extractFollows(ifStatement->getElseStatementList());
	processStatements(ifStatement->getElseStatementList());
	
}

void AbstractionExtractor::visitWhileStatement(shared_ptr<WhileStatement> whileStatement) {
	extractFollows(whileStatement->getStatementList());
	processStatements(whileStatement->getStatementList());
	extractParent(whileStatement->getStatementList(), whileStatement);
}