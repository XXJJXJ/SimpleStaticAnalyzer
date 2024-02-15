#include "QueryTokenizer.h"

QueryTokenizer::QueryTokenizer() {}
QueryTokenizer::~QueryTokenizer() {}


std::vector<std::vector<std::string>> QueryTokenizer::tokenize(const std::string& query) {
    std::vector<std::string> tokens;
    std::string token;
    bool trailingWhitespace = false;

    for (char c : query) {
        if (isspace(c)) {
            if (!token.empty()) {
                if (trailingWhitespace) {
                    // Remove trailing whitespace from token
                    while (!token.empty() && isspace(token.back())) {
                        token.pop_back();
                    }
                    if (!token.empty()) {
                        tokens.push_back(token);
                        token.clear();
                    }
                }
                else {
                    tokens.push_back(token);
                    token.clear();
                }
                trailingWhitespace = true;
            }
        }
        else {
            token.push_back(c);
            trailingWhitespace = false;
        }

        if (token.size() > 1 && isPunctuation(token.front())) {
            std::string punct(1, token.front());
            token.erase(0, 1); // Remove the leading punctuation
            tokens.push_back(punct);
        }

        if (token.size() > 1 && isPunctuation(token.back())) {
            std::string punct(1, token.back());
            token.pop_back();
            tokens.push_back(token);
            tokens.push_back(punct);
            token.clear();
        }
    }

    // Add the last token if it's not empty
    if (!token.empty()) {
        tokens.push_back(token);
    }

    return splitTokens(tokens);
}

bool QueryTokenizer::isPunctuation(char c) {
    return c == ',' || c == ';' || c == '(' || c == ')' || c == '<' || c == '>' || c == '_';
}

std::vector<std::vector<std::string>> QueryTokenizer::splitTokens(const std::vector<std::string>& tokens) {
    std::vector<std::vector<std::string>> lists;
    std::vector<std::string> currentList;

    for (const auto& token : tokens) {
        currentList.push_back(token);

        if (token == ";" || token == ")" || token == ">") {
            lists.push_back(currentList);
            currentList.clear();
        }
        else if (currentList.size() == 2 && currentList[0] == "Select" && token != "<") {
            // If the list starts with "Select", and the next token is not "<", end the list
            lists.push_back(currentList);
            currentList.clear();
        }
    }

    // Add the last list if it's not empty
    if (!currentList.empty()) {
        lists.push_back(currentList);
    }

    return lists;
}