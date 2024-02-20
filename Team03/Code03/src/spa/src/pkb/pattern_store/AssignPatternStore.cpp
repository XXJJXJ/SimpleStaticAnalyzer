#include "AssignPatternStore.h"



// Private functions
vector<shared_ptr<AssignStatement>> AssignPatternStore::matchPartial(vector<shared_ptr<AssignStatement>>& allAssign, string expr) {
    vector<shared_ptr<AssignStatement>> res;
    for (auto &s : allAssign) {
        if (partialMatch(s->getExpression(), expr).first) {
            res.push_back(s);
        }
    }
    return res;
}

vector<shared_ptr<AssignStatement>> AssignPatternStore::matchExact(vector<shared_ptr<AssignStatement>>& allAssign, string expr) {
    vector<shared_ptr<AssignStatement>> res;
    for (auto &s : allAssign) {
        if (fullMatch(s->getExpression(), expr).first) {
            res.push_back(s);
        }
    }
    return res;
}

pair<bool, string> AssignPatternStore::partialMatch(shared_ptr<Expression> exprS, string expr) {
    string val = exprS->getName();
    if (exprS->isLeafNodeExpression()) {
        return make_pair(val == expr, val);
    } else {
        auto args = exprS->getArguments();
        // guaranteed to have both left and right children in AssignStatement if not leaf node
        auto leftRes = partialMatch(args->first, expr);
        if (leftRes.first) {
            return leftRes;
        }
        auto rightRes = partialMatch(args->second, expr);
        if (rightRes.first) {
            return rightRes;
        }
        string res = leftRes.second.append(val).append(rightRes.second);
        return make_pair(res == expr, res);
    }
}

pair<bool, string> AssignPatternStore::fullMatch(shared_ptr<Expression> exprS, string expr) {
    string val = exprS->getName();
    if (exprS->isLeafNodeExpression()) {
        // then end already
        return make_pair(val == expr, val);
    } else {
        auto args = exprS->getArguments();
        // guaranteed to have both left and right children in AssignStatement if not leaf node
        auto leftRes = fullMatch(args->first, expr).second;
        auto rightRes = fullMatch(args->second, expr).second;
        string res = leftRes.append(val).append(rightRes);
        return make_pair(res == expr, res);
    }
}

// Public functions
bool AssignPatternStore::hasAssignPattern(string expr, bool hasWildcard) {
    if (hasWildcard) {
        return wildMatch.find(expr) != wildMatch.end();
    } else {
        return exactMatch.find(expr) != exactMatch.end();
    }
}

vector<shared_ptr<AssignStatement>> AssignPatternStore::getAssignPattern(string targetVar, string expr, bool hasWildcard) {
    vector<shared_ptr<AssignStatement>> res;
    if (hasWildcard) {
        if (targetVar == "") {
            return wildMatch[expr];
        }
        // Need to filter
        for (auto &s : wildMatch[expr]) {
            if (s->getVariable().getName() == targetVar) {
                res.push_back(s);
            }
        }
    } else {
        if (targetVar == "") {
            return exactMatch[expr];
        }
        for (auto &s : exactMatch[expr]) {
            if (s->getVariable().getName() == targetVar) {
                res.push_back(s);
            }
        }
    }
    return res;
}

vector<shared_ptr<AssignStatement>> AssignPatternStore::findAssignPattern(
    vector<shared_ptr<AssignStatement>>& allAssign, 
    string targetVar, string expr, bool hasWildcard) 
{
    if (expr == "" && hasWildcard) {
        wildMatch[expr] = allAssign;
    } else if (hasWildcard) {
        auto partialMatched = matchPartial(allAssign, expr);
        wildMatch[expr] = partialMatched;
    } else {
        auto exactMatched = matchExact(allAssign, expr);
        exactMatch[expr] = exactMatched;
    }
    // Reuse similar logic
    return getAssignPattern(targetVar, expr, hasWildcard);
}