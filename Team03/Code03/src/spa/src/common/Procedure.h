#pragma  once

#include <vector>

#include "Util.h"
#include "common/statement/Statement.h"
#include "Entity.h"

class Procedure : public Entity {
public:
	Procedure(string procedureName);
	void accept(shared_ptr<Visitor> visitor) override;
	void addToStatementList(shared_ptr<Statement> statement);
	string getName() const override;
	StatementList getStatementList() const;
    [[nodiscard]] EntityType getType() const override;
    [[nodiscard]] bool isOfType(EntityType type) const override;

private:
	string procedureName;
	StatementList statementList;
};