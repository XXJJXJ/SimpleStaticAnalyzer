#pragma once

#include "Visitor.h"
#include "../../common/Procedure.h"
#include "../../common/Variable.h"
#include "../../common/ReadStatement.h"
#include "../../common/PrintStatement.h"
#include "../../pkb/PopulatePKB.h"

class EntityExtractor : public Visitor {
public:
	typedef vector<shared_ptr<Statement>> StatementListContainer;
	EntityExtractor();
	void visitProcedure(shared_ptr<Procedure> procedure) override;
	void visitVariable(shared_ptr<Variable> variable) override;
	void visitReadStatement(shared_ptr<ReadStatement> read_statement) override;
	void visitPrintStatement(shared_ptr<PrintStatement> print_statement) override;
private:
	void processStatements(StatementListContainer &statements);
	shared_ptr<Populator> pkb_populator;
};