#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "common/Statement.h"
#include "common/Variable.h"

using namespace std;

// Used for if / while patterns
// if(v, _, _) or if (_, _, _) or if ("var", _, _)
// while(v, _) or while(_, _) or while("var", _)

// For each case just need to check direct uses of the if/while statements

class IfWhilePatternStore {
private:
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Variable>>> stmtToVar;

public:
    void add(shared_ptr<Statement> stmt, shared_ptr<Variable> var);
    vector<vector<shared_ptr<Entity>>> getPattern(const string& targetVar);
    void clear();
    ~IfWhilePatternStore();
};