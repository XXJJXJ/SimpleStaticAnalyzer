#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <regex>
#include "Token/Token.h"
#include "TokenFactory/NameTokenFactory.h"
#include "TokenFactory/PunctuationTokenFactory.h"
#include "TokenFactory/IntegerTokenFactory.h"
#include "TokenFactory/ArithmeticTokenFactory.h"
#include "TokenFactory/ConditionalTokenFactory.h"
#include "TokenFactory/RelationalTokenFactory.h"
#include "common/Util.h"
#include "common/spa_exception/SyntaxErrorException.h"

class Tokenizer {
public:
    Tokens tokenize(std::ifstream &file);
    shared_ptr<Token> stringToToken(std::string value);
};