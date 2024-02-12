#pragma once

#include <string>
#include <vector>
#include <memory>

#include "common/spa_exception/SemanticErrorException.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/Program.h"
#include "../tokenizer/Token.h"

class Parser {
public:
	shared_ptr<Program> parseSource(vector<shared_ptr<Token>> tokens);
};