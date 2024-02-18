#pragma once

#include <set>
#include <unordered_map>
#include "common/Statement.h"

using namespace std;

// Pure interface class
class StmtStmtStore {
public:
    virtual bool add(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) = 0;
    // using stmt - vector to accomodate parent
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getDirect() = 0;
    virtual unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> getTransitive() = 0;
    virtual void clear() = 0;
};