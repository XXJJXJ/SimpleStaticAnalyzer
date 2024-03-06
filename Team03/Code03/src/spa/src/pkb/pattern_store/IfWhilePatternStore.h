#pragma once

#include <unordered_map>
#include <unordered_set>

#include "common/Statement.h"

using namespace std;

// Used for if / while patterns
// if(v, _, _) or if (_, _, _) or if ("var", _, _)
// while(v, _) or while(_, _) or while("var", _)

// For each case just need to check direct uses of the if/while statements

class IfWhilePatternStore {
private:
    unordered_map<shared_ptr<Statement>, unordered_set<string>> matches;
public:
    void add(shared_ptr<Statement> stmt, const string& var);
    vector<shared_ptr<Entity>> getPattern(string& targetVar);
    void clear();
    ~IfWhilePatternStore();
};