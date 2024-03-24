#include "QueryTokenizer.h"
#include "common/spa_exception/SyntaxErrorException.h"

QueryTokenizer::QueryTokenizer() {}
QueryTokenizer::~QueryTokenizer() {}

std::vector<std::string> QueryTokenizer::tokenize(const std::string& query) { 
    std::vector<std::string> tokens = getTokens(query);
    std::vector<std::string> collapsedTokens = collapseTokens(tokens);

    return collapsedTokens;
}

std::vector<std::string> QueryTokenizer::getTokens(const std::string& query) { 
    std::vector<std::string> tokens = {};
    std::string currToken;

    for (char c : query) {
        if (isPunctuation(c)) {
            if (!currToken.empty()) {
                tokens.push_back(currToken);
                currToken.clear();
            }
            tokens.push_back({c});
        } else if (isspace(c) && !currToken.empty()) {
            tokens.push_back(currToken);
            currToken.clear();
        } else if (!isPunctuation(c) && !isspace(c)) {
            currToken.push_back(c);
        }
    }

    if (!currToken.empty()) {
        tokens.push_back(currToken);
    }

    return tokens;
}

std::vector<std::string> QueryTokenizer::collapseTokens(const std::vector<std::string>& tokens) { 
    std::vector<std::string> collapsedTokens = {};
    std::string currToken;

    bool isWithinWildcard = false;
    bool isWithinQuotes = false;
    bool isPrevSyn = false;

    for (std::string t : tokens) {
        if (isWithinQuotes) {
            if (t == "\"") {
                currToken.append(t);
                collapsedTokens.push_back(currToken);
                currToken.clear();
                isWithinQuotes = false;
            } else {
                currToken.append(t);
            }
        } else if (isWithinWildcard) {
            if ((t == ")" || t == ",") && currToken == "_") {
                collapsedTokens.push_back(currToken);
                collapsedTokens.push_back(t);
                isWithinWildcard = false;
                currToken.clear();
            } else if (t == "_") {
                currToken.append(t);
                collapsedTokens.push_back(currToken);
                currToken.clear();
                isWithinWildcard = false;
            } else {
                if (isPunctuation(t)) {
                    isPrevSyn = false;
                } else {
                    if (isPrevSyn){
                        currToken.append(" ");
                    }
                    isPrevSyn = true;
                }
                currToken.append(t);
            }
        } else {
            if (t == "_") {
                isWithinWildcard = true;
                currToken.append(t);
            } else if (t == "\"") {
                isWithinQuotes = true;
                currToken.append(t);
            } else {
                collapsedTokens.push_back(t);
            }
        }
    }
    if (!currToken.empty()) {
        collapsedTokens.push_back(currToken);
    }

    return collapsedTokens;
}


bool QueryTokenizer::isPunctuation(char c) {
    return c == ',' || c == ';' || c == '(' || c == ')' || c == '<' || c == '>' || c == '_' || c == '"';
}

bool QueryTokenizer::isPunctuation(std::string s) {
    return s == "," || s == ";" || s == "(" || s == ")" || s == "<" || s == ">" || s == "_" || s == "\"" || s == "+" || s == "-" || s == "*" || s == "/" || s == "%";
}