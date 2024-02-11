#pragma once
#include <string>
#include <vector>
#include "../tokenizer/Token.h"

template<typename Entity>
class EntityParser {
public:
	virtual shared_ptr<Entity> parseEntity(vector<shared_ptr<Token>> tokens) = 0;
};