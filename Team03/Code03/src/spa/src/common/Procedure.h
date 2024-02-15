#pragma  once

#include <vector>

#include "Util.h"
#include "Statement.h"
#include "Entity.h"

class Procedure : public Entity {
public:
	Procedure(string procedureName);
	void accept(shared_ptr<Visitor> visitor) override;
	void addToStatementList(shared_ptr<Statement> statement);
	string getName() const override;
	StatementListContainer getStatementList() const;

private:
	string procedureName;
	StatementListContainer statementList;
};