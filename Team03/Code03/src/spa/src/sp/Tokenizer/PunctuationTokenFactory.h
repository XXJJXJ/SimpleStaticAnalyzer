#pragma once

#include "TokenFactory.h"

class PunctuationTokenFactory : public TokenFactory {
public:
	static Token createToken(std::string value);
};