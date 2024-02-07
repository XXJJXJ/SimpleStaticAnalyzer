#pragma once

#include <string>
#include <optional>
#include "Entity.h"

class Expression : public Entity {
public:
    typedef pair<shared_ptr<Expression>, shared_ptr<Expression>>
        PairOfArguments;
    Expression() = default;
    explicit Expression(string name, string expression_type);
    virtual void accept(shared_ptr<Visitor> visitor) = 0;
    optional<PairOfArguments> getArguments() const;
    virtual inline bool isLeafNodeExpression() { return false; }
    string getExpressionType() const;
    string getName() const;
    virtual bool operator==(const Expression& other) const;
protected:
    optional<PairOfArguments> arguments;

private:
    string expression_type;
    string name;
};