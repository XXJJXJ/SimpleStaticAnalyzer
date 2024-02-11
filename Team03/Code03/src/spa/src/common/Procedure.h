#pragma  once

#include <vector>

#include "Statement.h"
#include "Entity.h"

class Procedure : public Entity {
public:
	typedef vector<shared_ptr<Statement>> StatementListContainer;
	Procedure(string procedureName);
	void accept(shared_ptr<Visitor> visitor) override;
	void addToStatementList(shared_ptr<Statement> statement);
	string getName() const override;
	shared_ptr<StatementListContainer> getStatementList() const;

private:
	string procedureName;
	shared_ptr<StatementListContainer> statementList;
};