#include "QueryTokenizer.h"
#include "common/spa_exception/SyntaxErrorException.h"

QueryTokenizer::QueryTokenizer() {}
QueryTokenizer::~QueryTokenizer() {}

// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4ba78f27-8cc9-4e4b-887d-4f9689d236b1

//std::vector<std::string> QueryTokenizer::tokenize(const std::string& query) {
//    std::vector<std::string> tokens;
//    std::string token;
//    bool trailingWhitespace = false;
//    bool isWithinQuotes = false;
//    bool isWithinWildcard = false;
//    for (char c : query) {
//        if (isWithinQuotes) {
//            trailingWhitespace = false;
//            token.push_back(c);
//            if (c == '"') {
//                isWithinQuotes = !isWithinQuotes;
//                if (!isWithinWildcard) {
//                    tokens.push_back(token);
//                    token.clear();
//                }
//            }
//        }
//        else if (isWithinWildcard) {
//            trailingWhitespace = false;
//
//            if (c == '"') {
//                token.push_back(c);
//                isWithinQuotes = !isWithinQuotes;
//            }
//            else if (c == ',' || c == ')') {
//                tokens.push_back(token);
//                token.clear();
//                isWithinWildcard = !isWithinWildcard;
//                token.push_back(c);
//                tokens.push_back(token);
//                token.clear();
//            }
//            else {
//                token.push_back(c);
//                if (c == '_') {
//                    isWithinWildcard = !isWithinWildcard;
//                    tokens.push_back(token);
//                    token.clear();
//                }
//            }
//        }
//        else {
//            if (isspace(c)) {
//                if (!token.empty()) {
//                    if (trailingWhitespace) {
//                        // Remove trailing whitespace from token
//                        while (!token.empty() && isspace(token.back())) {
//                            token.pop_back();
//                        }
//                        if (!token.empty()) {
//                            tokens.push_back(token);
//                            token.clear();
//                        }
//                    }
//                    else {
//                        tokens.push_back(token);
//                        token.clear();
//                    }
//                    trailingWhitespace = true;
//                }
//            }
//            else {
//                trailingWhitespace = false;
//                token.push_back(c);
//                isWithinQuotes = c == '"';
//                isWithinWildcard = c == '_';
//            }
//
//            if (token.size() > 1 && isPunctuation(token.front())) {
//                std::string punct(1, token.front());
//                token.erase(0, 1); // Remove the leading punctuation
//                tokens.push_back(punct);
//            }
//
//            if (token.size() > 1 && isPunctuation(token.back())) {
//                std::string punct(1, token.back());
//                token.pop_back();
//                tokens.push_back(token);
//                tokens.push_back(punct);
//                token.clear();
//            }
//        }
//    }
//
//    // Add the last token if it's not empty
//    if (!token.empty()) {
//        tokens.push_back(token);
//    }
//
//    return tokens;
//}


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
                currToken.append(t);
            }
        } else {
            if (t == "_") {
                isWithinWildcard = true;
                currToken.append(t);
                collapsedTokens.push_back(t);
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

// ai-gen end