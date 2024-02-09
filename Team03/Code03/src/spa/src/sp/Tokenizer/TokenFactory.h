#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

class TokenFactory {
	static Token createToken(string value);
};