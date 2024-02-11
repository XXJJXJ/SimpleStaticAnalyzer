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
    void accept(shared_ptr<Visitor> visitor) override = 0;
    int getStatementNumber() const;
    string getStatementType() const;
    string getProcedureName() const;
    string getName() const override;

private:
    const int statementNumber;
    string statementType;
    string procedureName;
};