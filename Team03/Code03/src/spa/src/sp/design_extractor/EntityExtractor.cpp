#include "EntityExtractor.h"

EntityExtractor::EntityExtractor() {
	pkb_populator = make_shared<Populator>();
}

void EntityExtractor::processStatements(EntityExtractor::StatementListContainer &statements) {
	for (auto s : statements) {
		s->accept(make_shared<EntityExtractor>(*this));
	}
}

void EntityExtractor::visitReadStatement(shared_ptr<ReadStatement> read_statement) {
	pkb_populator->addVariable(read_statement->getVariable());
	pkb_populator->addReadStatement(read_statement);
}

void EntityExtractor::visitPrintStatement(shared_ptr<PrintStatement> print_statement) {
	pkb_populator->addVariable(print_statement->getVariable());
	pkb_populator->addPrintStatement(print_statement);
}

void EntityExtractor::visitProcedure(shared_ptr<Procedure> procedure) {
	processStatements(procedure->getStatementList());
	pkb_populator->addProcedure(procedure);
}

void EntityExtractor::visitVariable(shared_ptr<Variable> variable) {
	pkb_populator->addVariable(variable);
}