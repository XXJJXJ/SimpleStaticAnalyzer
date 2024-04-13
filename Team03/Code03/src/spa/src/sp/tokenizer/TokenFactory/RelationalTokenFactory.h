#pragma once

#include "TokenFactory.h"

class RelationalTokenFactory : public TokenFactory {
public:
    static shared_ptr<Token> createToken(std::string value);
};