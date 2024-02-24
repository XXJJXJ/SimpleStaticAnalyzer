#include "EntityExtractor.h"

EntityExtractor::EntityExtractor(shared_ptr<Populator> pkb) {
	pkbPopulator = pkb;
}

void EntityExtractor::processStatements(StatementListContainer statementList) {
	for (auto s : statementList) {
		s->accept(make_shared<EntityExtractor>(*this));
	}
}

void EntityExtractor::extractArgs(optional<PairOfArguments> arguments) {
	auto &[lhs, rhs] = *arguments;
	if (lhs) {
		lhs->accept(make_shared<EntityExtractor>(*this));
	}
	if (rhs) {
		rhs->accept(make_shared<EntityExtractor>(*this));
	}
}

void EntityExtractor::visitReadStatement(shared_ptr<ReadStatement> readStatement) {
	pkbPopulator->addVariable(readStatement->getVariable());
	pkbPopulator->addReadStatement(readStatement);
}

void EntityExtractor::visitPrintStatement(shared_ptr<PrintStatement> printStatement) {
	pkbPopulator->addVariable(printStatement->getVariable());
	pkbPopulator->addPrintStatement(printStatement);
}

void EntityExtractor::visitProcedure(shared_ptr<Procedure> procedure) {
	processStatements(procedure->getStatementList());
	pkbPopulator->addProcedure(procedure);
}

void EntityExtractor::visitVariable(shared_ptr<Variable> variable) {
	pkbPopulator->addVariable(variable);
}

void EntityExtractor::visitConstant(shared_ptr<Constant> constant) {
	pkbPopulator->addConstant(constant);
};

void EntityExtractor::visitArithmeticalOperation(shared_ptr<ArithmeticOperation> arithmeticOperation) {
	extractArgs(arithmeticOperation->getArguments());
};

void EntityExtractor::visitAssignStatement(shared_ptr<AssignStatement> assignStatement) {
	pkbPopulator->addAssignStatement(assignStatement);
};

void EntityExtractor::visitConditionalOperation(shared_ptr<ConditionalOperation> conditionalOperation) {
	extractArgs(conditionalOperation->getArguments());
};

void EntityExtractor::visitRelationalOperation(shared_ptr<RelationalOperation> relationalOperation) {
	extractArgs(relationalOperation->getArguments());
};

void EntityExtractor::visitIfStatement(shared_ptr<IfStatement> ifStatement) {
	auto condition = ifStatement->getCondition();
	condition->accept(make_shared<EntityExtractor>(*this));
	pkbPopulator->addIfStatement(ifStatement);
	processStatements(ifStatement->getThenStatementList());
	processStatements(ifStatement->getElseStatementList());

};

void EntityExtractor::visitWhileStatement(shared_ptr<WhileStatement> whileStatement) {
	auto condition = whileStatement->getCondition();
	condition->accept(make_shared<EntityExtractor>(*this));
	pkbPopulator->addWhileStatement(whileStatement);
	processStatements(whileStatement->getStatementList());
};