#pragma once

#include <string>
#include <optional>
#include "Entity.h"

class Expression : public Entity {
public:
    typedef pair<shared_ptr<Expression>, shared_ptr<Expression>>
        PairOfArguments;
    explicit Expression(shared_ptr<string> name, shared_ptr<string> expressiontType);
    virtual void accept(shared_ptr<Visitor> visitor) = 0;
    optional<PairOfArguments> getArguments() const;
    shared_ptr<string> getExpressionType() const;
    shared_ptr<string> getName() const;
    virtual inline bool isLeafNodeExpression() { return false; }
    virtual bool operator==(const Expression& other) const;

protected:
    optional<PairOfArguments> arguments;

private:
    shared_ptr<string> expressionType;
    shared_ptr<string> name;
};