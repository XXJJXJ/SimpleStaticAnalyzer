#include "../Token/RelationalToken.h"
#include "RelationalTokenFactory.h"

shared_ptr<Token> RelationalTokenFactory::createToken(std::string value) {
	return make_shared<RelationalToken>(value);
}