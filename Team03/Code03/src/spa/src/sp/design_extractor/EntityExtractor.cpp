#include "EntityExtractor.h"

EntityExtractor::EntityExtractor() {
	pkbPopulator = make_shared<Populator>();
}

void EntityExtractor::processStatements(Procedure::StatementListContainer statementList) {
	for (auto s : statementList) {
		s->accept(make_shared<EntityExtractor>(*this));
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