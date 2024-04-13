#pragma once

#include <stdio.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "../Token/Token.h"

class TokenFactory {
public:
	static std::shared_ptr<Token> createToken(string value);
};