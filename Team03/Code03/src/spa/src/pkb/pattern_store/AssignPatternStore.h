#pragma once

#include <unordered_map>
#include "common/AssignStatement.h"

class AssignPatternStore {
private:
    unordered_map<string, vector<shared_ptr<AssignStatement>>> wildMatch;
    unordered_map<string, vector<shared_ptr<AssignStatement>>> exactMatch;

    vector<shared_ptr<AssignStatement>> matchPartial(vector<shared_ptr<AssignStatement>>& allAssign, string expr);
    vector<shared_ptr<AssignStatement>> matchExact(vector<shared_ptr<AssignStatement>>& allAssign, string expr);
    pair<bool, string> partialMatch(shared_ptr<Expression> exprS, string expr);
    pair<bool, string> fullMatch(shared_ptr<Expression> exprS, string expr);
public:
    bool hasAssignPattern(string expr, bool hasWildcard);
    vector<shared_ptr<AssignStatement>> getAssignPattern(string targetVar, string expr, bool hasWildcard);
    vector<shared_ptr<AssignStatement>> findAssignPattern(vector<shared_ptr<AssignStatement>>& allAssign, string targetVar, string expr, bool hasWildcard);
};