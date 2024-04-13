#pragma once

#include "TokenFactory.h"

class ConditionalTokenFactory : public TokenFactory {
public:
    static shared_ptr<Token> createToken(std::string value);
};