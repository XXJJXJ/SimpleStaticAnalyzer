#include "RelationalToken.h"

RelationalToken::RelationalToken(std::string value) : Token(getTokenTypeFromValue(value), value) {};

TokenType RelationalToken::getTokenTypeFromValue(std::string value) {
    if (value == "<") {
        return TokenType::LESS_THAN;
    } else if (value == "<=") {
        return TokenType::LESS_THAN_EQUAL;
    } else if (value == ">") {
        return TokenType::GREATER_THAN;
    } else if (value == ">=") {
        return TokenType::GREATER_THAN_EQUAL;
    } else if (value == "==") {
        return TokenType::DOUBLE_EQUALS;
    } else if (value == "!=") {
        return TokenType::NOT_EQUAL;
    } else {
        return TokenType::INVALID;
    }
}