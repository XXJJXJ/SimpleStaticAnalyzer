#pragma once

#include <string>
#include <vector>
#include "Entity.h"

class Statement : public Entity {
public:
    Statement(
        int statementNumber,
        string statementType,
        string procedureName);
    virtual void accept(shared_ptr<Visitor> visitor) = 0;
    int getStatementNumber() const;
    string getStatementType() const;
    string getProcedureName() const;

private:
    const int statementNumber;
    string statementType;
    string procedureName;
};