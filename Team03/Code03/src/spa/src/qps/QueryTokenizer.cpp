#include "QueryTokenizer.h"
#include "qps/util/QueryTokenValidator.h"

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
            handleWithinQuotes(t, currToken, collapsedTokens, isWithinQuotes, isPrevSyn);
        } else if (isWithinWildcard) {
            handleWithinWildcard(t, currToken, collapsedTokens, isWithinWildcard, isPrevSyn);
        } else {
            handleNormalToken(t, currToken, collapsedTokens, isWithinQuotes, isWithinWildcard);
        }
    }

    if (!currToken.empty()) {
        collapsedTokens.push_back(currToken);
    }

    return collapsedTokens;
}

void QueryTokenizer::handleWithinQuotes(std::string& t, std::string& currToken, std::vector<std::string>& collapsedTokens, bool& isWithinQuotes, bool& isPrevSyn) {
    if (t == "\"") {
        currToken.append(t);
        collapsedTokens.push_back(currToken);
        currToken.clear();
        isWithinQuotes = false;
    } else {
        handleCollapsingTokens(t, currToken, isPrevSyn);
    }
}

void QueryTokenizer::handleWithinWildcard(std::string& t, std::string& currToken, std::vector<std::string>& collapsedTokens, bool& isWithinWildcard, bool& isPrevSyn) {
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
        handleCollapsingTokens(t, currToken, isPrevSyn);
    }
}

void QueryTokenizer::handleNormalToken(std::string& t, std::string& currToken, std::vector<std::string>& collapsedTokens, bool& isWithinQuotes, bool& isWithinWildcard) {
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

void QueryTokenizer::handleCollapsingTokens(std::string& t, std::string& currToken, bool& isPrevSyn) {
    if (QueryTokenValidator::isIdent(t)) {
        if (isPrevSyn){
            currToken.append(" ");
        }
        isPrevSyn = true;
    } else {
        isPrevSyn = false;
    }
    currToken.append(t);
}

bool QueryTokenizer::isPunctuation(char c) {
    return c == ',' || c == ';' || c == '(' || c == ')' || c == '<' || c == '>' || c == '_' || c == '"' || c == '=';
}