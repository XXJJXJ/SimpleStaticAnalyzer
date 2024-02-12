#pragma once

#include <stdio.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Token.h"

class TokenFactory {
	static std::shared_ptr<Token> createToken(string value);
};