#pragma once

#include <string>
#include <vector>
#include "Entity.h"

class Statement : public Entity {
public:
    Statement(
        int statement_number,
        string statement_type,
        string procedure_name);
    virtual void accept(shared_ptr<Visitor> visitor) = 0;
    int getStatementNumber() const;
    string getStatementType() const;
    string getProcedureName() const;

private:
    const int statement_number;
    string statement_type;
    string procedure_name;
};