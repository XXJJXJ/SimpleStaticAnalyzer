#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <regex>
#include "Token.h"
#include "NameTokenFactory.h"
#include "PunctuationTokenFactory.h"

class Tokenizer {
public:
	std::vector<shared_ptr<Token>> tokenize(std::ifstream& file);

	shared_ptr<Token> stringToToken(std::string value);
};