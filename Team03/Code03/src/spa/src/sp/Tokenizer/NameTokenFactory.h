#pragma once

#include "TokenFactory.h"

class NameTokenFactory : public TokenFactory {
public:
	static Token createToken(std::string value);
};