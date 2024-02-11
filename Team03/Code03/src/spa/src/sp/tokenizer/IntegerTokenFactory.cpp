#include "IntegerToken.h"
#include "IntegerTokenFactory.h"

shared_ptr<Token> IntegerTokenFactory::createToken(std::string value) {
	return make_shared<IntegerToken>(value);
}