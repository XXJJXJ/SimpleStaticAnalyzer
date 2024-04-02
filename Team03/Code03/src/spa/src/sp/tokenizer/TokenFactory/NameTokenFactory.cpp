#include "../Token/NameToken.h"
#include "NameTokenFactory.h"

shared_ptr<Token> NameTokenFactory::createToken(std::string value) {
	return make_shared<NameToken>(value);
}