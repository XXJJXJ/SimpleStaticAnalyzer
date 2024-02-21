#include "AssignPatternStore.h"



// Private functions
vector<shared_ptr<AssignStatement>> AssignPatternStore::matchPartial(vector<shared_ptr<AssignStatement>>& allAssign, string& expr) {
    vector<shared_ptr<AssignStatement>> res;
    for (auto &s : allAssign) {
        string curr;
        if (partialMatch(s->getExpression(), curr, expr)) {
            res.push_back(s);
        }
    }
    return res;
}

vector<shared_ptr<AssignStatement>> AssignPatternStore::matchExact(vector<shared_ptr<AssignStatement>>& allAssign, string& expr) {
    vector<shared_ptr<AssignStatement>> res;
    for (auto &s : allAssign) {
        string curr;
        if (fullMatch(s->getExpression(), curr, expr)) {
            res.push_back(s);
        }
    }
    return res;
}

bool AssignPatternStore::partialMatch(shared_ptr<Expression> exprS, string& curr, string& expr) {
    string val = exprS->getName();
    if (exprS->isLeafNodeExpression()) {
        curr.append(val);
        return curr == expr;
    } else {
        auto args = exprS->getArguments();
        // guaranteed to have both left and right children in AssignStatement if not leaf node
        auto leftRes = partialMatch(args->first, curr, expr);
        if (leftRes) {
            return leftRes;
        }
        string rightCurr = "";
        auto rightRes = partialMatch(args->second, rightCurr, expr);
        if (rightRes) {
            return rightRes;
        }
        curr.append(val).append(rightCurr);
        return curr == expr;
    }
}

bool AssignPatternStore::fullMatch(shared_ptr<Expression> exprS, string& curr, string& expr) {
    string val = exprS->getName();
    if (exprS->isLeafNodeExpression()) {
        curr.append(val);
        return curr == expr;
    } else {
        auto args = exprS->getArguments();
        // guaranteed to have both left and right children in AssignStatement if not leaf node
        fullMatch(args->first, curr, expr);
        string rightCurr = "";
        fullMatch(args->second, rightCurr, expr);
        curr.append(val).append(rightCurr);
        return curr == expr;
    }
}

// Public functions
bool AssignPatternStore::hasAssignPattern(string& expr, bool hasWildcard) {
    if (hasWildcard) {
        return wildMatch.find(expr) != wildMatch.end();
    } else {
        return exactMatch.find(expr) != exactMatch.end();
    }
}

vector<shared_ptr<AssignStatement>> AssignPatternStore::getAssignPattern(string& targetVar, string& expr, bool hasWildcard) {
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
    string& targetVar, string& expr, bool hasWildcard) 
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

void AssignPatternStore::clear() {
    wildMatch.clear();
    exactMatch.clear();
}