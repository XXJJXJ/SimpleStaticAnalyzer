#include "QueryTokenizer.h"
#include "common/spa_exception/SyntaxErrorException.h"

QueryTokenizer::QueryTokenizer() {}
QueryTokenizer::~QueryTokenizer() {}

// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4ba78f27-8cc9-4e4b-887d-4f9689d236b1

/*
Tokenizing steps:
1. Split query into tokens using space or punctuations as delimters. Keep delimiters in the list if it is not a space.
2. Split tokens into multiple lists, each list is a component of a query (Declarations, Selections, Clauses).
3. Each list contains items, where each item is a list of tokens 
4. Identifying a Declaration: ends with `;`
5. Identifying a Selection: EITHER first word of list == "Select" and second token != `<`, end here OR last token is `>`.
6. Identifying a Clause: ends with `)`, only when all opening `(` have been closed by a matching `)`
*/
std::vector<std::vector<std::vector<std::string>>> QueryTokenizer::tokenize(const std::string& query) {
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

std::vector<std::vector<std::vector<std::string>>> QueryTokenizer::splitTokens(const std::vector<std::string>& tokens) {
    std::vector<std::string> currentList;
    int openParenthesesCount = 0;

    std::vector<std::vector<std::vector<std::string>>> splitTokens = {};
    std::vector<std::vector<std::string>> declarations;
    std::vector<std::vector<std::string>> selections;
    std::vector<std::vector<std::string>> clauses;

    bool isClause = false;

    for (const auto& token : tokens) {
        currentList.push_back(token);

        if (token == "(") {
            openParenthesesCount++;
        }
        else if (token == ")") {
            openParenthesesCount--;
            if (openParenthesesCount < 0) {
                throw SyntaxErrorException("Mismatched parentheses");
            }
            else if (openParenthesesCount == 0) {
                if (!isClause) {
                    throw SyntaxErrorException("Incorrect order in query");
                }
                clauses.push_back(currentList);
                currentList.clear();
            }
        }
        else if (token == ";") {
            if (isClause) {
                throw SyntaxErrorException("Incorrect order in query");
            }
            declarations.push_back(currentList);
            currentList.clear();
        }
        else if (token == ">" && currentList[0] == "Select") {
            if (isClause) {
                throw SyntaxErrorException("Incorrect order in query");
            }
            selections.push_back(currentList);
            currentList.clear();
            isClause = true;
        }
        else if (currentList.size() == 2 && currentList[0] == "Select" && token != "<") {
            // If the list starts with "Select", and the next token is not "<", end the list
            if (isClause) {
                throw SyntaxErrorException("Incorrect order in query");
            }
            selections.push_back(currentList);
            currentList.clear();
            isClause = true;
        }
    }

    // Query does not end properly
    if (!currentList.empty()) {
        throw SyntaxErrorException("Invalid query syntax");
    }

    splitTokens.push_back(declarations);
    splitTokens.push_back(selections);
    splitTokens.push_back(clauses);

    return splitTokens;
}

// ai-gen end