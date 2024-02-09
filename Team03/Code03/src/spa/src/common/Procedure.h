#pragma  once

#include <vector>

#include "Statement.h"
#include "Entity.h"

class Procedure : public Entity {
public:
	typedef vector<shared_ptr<Statement>> StatementListContainer;
	Procedure(shared_ptr<string> procedureName);
	void accept(shared_ptr<Visitor> visitor) override;
	void addToStatementList(shared_ptr<Statement> statement);
	shared_ptr<string> getProcedureName() const;
	shared_ptr<StatementListContainer> getStatementList() const;

private:
	shared_ptr<string> procedureName;
	shared_ptr<StatementListContainer> statementList;
};