#pragma once

#include <string>
#include <vector>
#include "../tokenizer/Token.h"

template<typename Entity>
class EntityParser {
public:
	typedef vector<shared_ptr<Token>> Tokens;
	virtual shared_ptr<Entity> parseEntity(vector<shared_ptr<Token>>& tokens) = 0;
};