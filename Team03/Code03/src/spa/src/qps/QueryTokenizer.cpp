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

    bool isWithinWildcard = false;
    bool isWithinQuotes = false;
    bool isPrevSyn = false;
    bool isAttrRef = false;

    for (std::string t : tokens) {
        if (isWithinQuotes) {
            handleWithinQuotes(t, collapsedTokens, isWithinQuotes, isPrevSyn);
        } else if (isWithinWildcard) {
            handleWithinWildcard(t, collapsedTokens, isWithinWildcard, isPrevSyn);
        } else if (isAttrRef) {
            collapsedTokens.back().append(t);
            isAttrRef = false;
        } else {
            handleNormalToken(t, collapsedTokens, isWithinQuotes, isWithinWildcard, isAttrRef);
        }
    }

    return collapsedTokens;
}

void QueryTokenizer::handleWithinQuotes(std::string& t, std::vector<std::string>& collapsedTokens, bool& isWithinQuotes, bool& isPrevSyn) {
    if (t == "\"") {
        collapsedTokens.back().append(t);
        isWithinQuotes = false;
        isPrevSyn = false;
    } else {
        handleCollapsingTokens(t, collapsedTokens, isPrevSyn);
    }
}

void QueryTokenizer::handleWithinWildcard(std::string& t, std::vector<std::string>& collapsedTokens, bool& isWithinWildcard, bool& isPrevSyn) {
    if ((t == ")" || t == ",") && collapsedTokens.back() == "_") {
        collapsedTokens.push_back(t);
        isWithinWildcard = false;
    } else if (t == "_") {
        collapsedTokens.back().append(t);
        isWithinWildcard = false;
        isPrevSyn = false;
    } else {
        handleCollapsingTokens(t, collapsedTokens, isPrevSyn);
    }
}

void QueryTokenizer::handleNormalToken(std::string& t, std::vector<std::string>& collapsedTokens, bool& isWithinQuotes, bool& isWithinWildcard, bool& isAttrRef) {
    if (t == "_") {
        isWithinWildcard = true;
        collapsedTokens.push_back(t);
    } else if (t == "\"") {
        isWithinQuotes = true;
        collapsedTokens.push_back(t);
    } else if (t == ".") {
        collapsedTokens.back().append(t);
        isAttrRef = true;
    } else {
        collapsedTokens.push_back(t);
    }
}

void QueryTokenizer::handleCollapsingTokens(std::string& t, std::vector<std::string>& collapsedTokens, bool& isPrevSyn) {
    if (QueryTokenValidator::isIdent(t)) {
        if (isPrevSyn){
            collapsedTokens.back().append(" ");
        }
        isPrevSyn = true;
    } else {
        isPrevSyn = false;
    }
    collapsedTokens.back().append(t);
}

bool QueryTokenizer::isPunctuation(char c) {
    return c == ',' || c == ';' || c == '(' || c == ')' || c == '<' || c == '>' || c == '_' || c == '"' || c == '=' || c == '.';
}