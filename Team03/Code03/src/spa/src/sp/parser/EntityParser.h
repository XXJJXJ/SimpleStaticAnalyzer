#pragma once
#include <string>
#include <vector>
#include "../tokenizer/token.h"

template<typename Entity>
class EntityParser {
public:
	virtual shared_ptr<Entity> parseEntity(vector<shared_ptr<Token>> tokens) = 0;
};