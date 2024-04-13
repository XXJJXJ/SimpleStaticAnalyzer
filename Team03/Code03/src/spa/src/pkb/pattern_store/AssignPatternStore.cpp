#include "AssignPatternStore.h"

// ai-gen start(gpt, 2, e)
// prompt: https://platform.openai.com/playground/p/NO2qblo8fQIgUUtE5l7Cz01B?model=gpt-4&mode=chat
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

// Function is long, but there is no good way to shorten 
// (Don't comment for the sake of commenting, unless you have a good concrete suggestion)
string infixToPostfix(std::string expression) {
    string result = "";
    stack<char> operators;
    map<char, int> precedence;
    precedence['+'] = precedence['-'] = 1;
    precedence['*'] = precedence['/'] = precedence['%'] = 2;

    for (size_t i = 0; i < expression.length(); ++i) {
        if (expression[i] == '(') {
            int count = 1;
            i++;
            string temp;
            // Find the proper end
            while (i < expression.length() && count > 0) {
                if (expression[i] == '(') count++;
                if (expression[i] == ')') count--;
                if (count > 0) temp += expression[i];
                i++;
            }
            i--;
            string res = infixToPostfix(temp);
            result += res;
        } else if (!isOperator(expression[i]) || isdigit(expression[i])) {
            // is a synonym: assumes no spaces and no random '(' or ')' characters
            // reads in until the next operator
            while (i < expression.length() && !isOperator(expression[i])) {
                result += expression[i];
                ++i;
            }
            --i;
            result += " ";
        } else {
            while (!operators.empty() && precedence[operators.top()] >= precedence[expression[i]]) {
                result += operators.top();
                result += " ";
                operators.pop();
            }
            operators.push(expression[i]);
        }
    }

    while (!operators.empty()) {
        result += operators.top();
        result += " ";
        operators.pop();
    }
    return result;
}
// ai-gen end

// Private functions
vector<shared_ptr<AssignStatement>> AssignPatternStore::matchPartial(vector<shared_ptr<AssignStatement>>& allAssign, string& rpn) {
    vector<shared_ptr<AssignStatement>> res;
    for (auto &s : allAssign) {
        string curr;
        if (partialMatch(s->getExpression(), curr, rpn)) {
            res.push_back(s);
        }
    }
    return res;
}

vector<shared_ptr<AssignStatement>> AssignPatternStore::matchExact(vector<shared_ptr<AssignStatement>>& allAssign, string& rpn) {
    vector<shared_ptr<AssignStatement>> res;
    for (auto &s : allAssign) {
        string curr;
        if (fullMatch(s->getExpression(), curr, rpn)) {
            res.push_back(s);
        }
    }
    return res;
}

bool AssignPatternStore::partialMatch(shared_ptr<Expression> exprS, string& curr, string& rpn) {
    string val = exprS->getName();
    if (exprS->isLeafNode()) {
        curr.append(val).append(" ");
        return curr == rpn;
    } else {
        auto args = exprS->getArguments();
        // guaranteed to have both left and right children in AssignStatement if not leaf node
        auto leftRes = partialMatch(args->first, curr, rpn);
        if (leftRes) {
            return leftRes;
        }
        string rightCurr = "";
        auto rightRes = partialMatch(args->second, rightCurr, rpn);
        if (rightRes) {
            return rightRes;
        }
        curr.append(rightCurr).append(val).append(" ");
        return curr == rpn;
    }
}

bool AssignPatternStore::fullMatch(shared_ptr<Expression> exprS, string& curr, string& rpn) {
    string val = exprS->getName();
    if (exprS->isLeafNode()) {
        curr.append(val).append(" ");
        return curr == rpn;
    } else {
        auto args = exprS->getArguments();
        // guaranteed to have both left and right children in AssignStatement if not leaf node
        fullMatch(args->first, curr, rpn);
        string rightCurr = "";
        fullMatch(args->second, rightCurr, rpn);
        curr.append(rightCurr).append(val).append(" ");
        return curr == rpn;
    }
}

// Public functions
bool AssignPatternStore::hasAssignPattern(string& expr, bool hasWildcard) {
    string rpn = infixToPostfix(expr);
    if (hasWildcard) {
        return wildMatch.find(rpn) != wildMatch.end();
    } else {
        return exactMatch.find(rpn) != exactMatch.end();
    }
}

vector<vector<shared_ptr<Entity>>> AssignPatternStore::getAssignPattern(string& expr, bool hasWildcard) {
    string rpn = infixToPostfix(expr);
    vector<vector<shared_ptr<Entity>>> res;
    if (hasWildcard) {
        for (auto &s : wildMatch[rpn]) {
            res.push_back({s, s->getVariable()});
        }
    } else {
        for (auto &s : exactMatch[rpn]) {
            res.push_back({s, s->getVariable()});
        }
    }
    return res;
}

vector<vector<shared_ptr<Entity>>> AssignPatternStore::findAssignPattern(
    vector<shared_ptr<AssignStatement>>& allAssign, 
    string& expr, bool hasWildcard) 
{
    string rpn = infixToPostfix(expr);
    if (expr == "" && hasWildcard) {
        wildMatch[expr] = allAssign;
    } else if (hasWildcard) {
        auto partialMatched = matchPartial(allAssign, rpn);
        wildMatch[rpn] = partialMatched;
    } else {
        auto exactMatched = matchExact(allAssign, rpn);
        exactMatch[rpn] = exactMatched;
    }
    // Reuse similar logic
    return getAssignPattern(expr, hasWildcard);
}

void AssignPatternStore::clear() {
    wildMatch.clear();
    exactMatch.clear();
}

AssignPatternStore::~AssignPatternStore() {
    clear();
}