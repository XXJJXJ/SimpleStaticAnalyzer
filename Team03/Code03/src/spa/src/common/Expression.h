#pragma once

#include <string>
#include <optional>
#include "Entity.h"

class Expression : public Entity {
public:
    typedef pair<shared_ptr<Expression>, shared_ptr<Expression>>
        PairOfArguments;
    explicit Expression(string name, string expressiontType);
    virtual void accept(shared_ptr<Visitor> visitor) = 0;
    optional<PairOfArguments> getArguments() const;
    string getExpressionType() const;
    string getName() const;
    virtual inline bool isLeafNodeExpression() { return false; }
    virtual bool operator==(const Expression& other) const;

protected:
    optional<PairOfArguments> arguments;

private:
    string expressionType;
    string name;
};