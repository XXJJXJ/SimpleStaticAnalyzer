#include "EntityExtractor.h"

EntityExtractor::EntityExtractor() {
	pkb_populator = make_shared<Populator>();
}

void EntityExtractor::processStatements(Procedure::StatementListContainer statements) {
	for (auto s : statements) {
		s->accept(make_shared<EntityExtractor>(*this));
	}
}

void EntityExtractor::visitReadStatement(shared_ptr<ReadStatement> readStatement) {
	pkb_populator->addVariable(readStatement->getVariable());
	pkb_populator->addReadStatement(readStatement);
}

void EntityExtractor::visitPrintStatement(shared_ptr<PrintStatement> printStatement) {
	pkb_populator->addVariable(printStatement->getVariable());
	pkb_populator->addPrintStatement(printStatement);
}

void EntityExtractor::visitProcedure(shared_ptr<Procedure> procedure) {
	processStatements(procedure->getStatementList());
	pkb_populator->addProcedure(procedure);
}

void EntityExtractor::visitVariable(shared_ptr<Variable> variable) {
	pkb_populator->addVariable(variable);
}