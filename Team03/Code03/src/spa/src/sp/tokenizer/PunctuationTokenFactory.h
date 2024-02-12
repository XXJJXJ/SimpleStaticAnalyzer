#pragma once

#include "TokenFactory.h"

class PunctuationTokenFactory : public TokenFactory {
public:
	static shared_ptr<Token> createToken(std::string value);
};