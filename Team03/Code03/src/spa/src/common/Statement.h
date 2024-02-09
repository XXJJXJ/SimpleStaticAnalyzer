#pragma once

#include <string>
#include <vector>
#include "Entity.h"

class Statement : public Entity {
public:
    Statement(
        shared_ptr<int> statementNumber,
        shared_ptr<string> statementType,
        shared_ptr<string> procedureName);
    virtual void accept(shared_ptr<Visitor> visitor) = 0;
    shared_ptr<int> getStatementNumber() const;
    shared_ptr<string> getStatementType() const;
    shared_ptr<string> getProcedureName() const;

private:
    const shared_ptr<int> statementNumber;
    shared_ptr<string> statementType;
    shared_ptr<string> procedureName;
};