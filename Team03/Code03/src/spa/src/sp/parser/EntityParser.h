#pragma once

#include <string>
#include <vector>
#include "../tokenizer/Token.h"

template<typename Entity>
class EntityParser {
public:
	virtual shared_ptr<Entity> parseEntity(Tokens& tokens) = 0;
};