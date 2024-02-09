#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "Token.h"
#include "NameTokenFactory.h"
#include "PunctuationTokenFactory.h"

class Tokenizer {
public:
	//std::vector<Token> tokenize(std::ifstream file);

	std::vector<Token> tokenize(std::string str);

	Token stringToToken(std::string value);
};