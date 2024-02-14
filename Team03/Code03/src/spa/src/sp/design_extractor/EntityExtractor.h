#pragma once

#include "Visitor.h"
#include "../../common/Procedure.h"
#include "../../common/Variable.h"
#include "../../common/ReadStatement.h"
#include "../../common/PrintStatement.h"
#include "../../pkb/PopulatePKB.h"

class EntityExtractor : public Visitor {
public:
	EntityExtractor();
	void visitProcedure(shared_ptr<Procedure> procedure) override;
	void visitVariable(shared_ptr<Variable> variable) override;
	void visitReadStatement(shared_ptr<ReadStatement> readStatement) override;
	void visitPrintStatement(shared_ptr<PrintStatement> printStatement) override;
private:
	void processStatements(Procedure::StatementListContainer statementList);
	shared_ptr<Populator> pkbPopulator;
};