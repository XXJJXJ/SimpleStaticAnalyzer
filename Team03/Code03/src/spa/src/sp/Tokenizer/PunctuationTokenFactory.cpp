#include "PunctuationToken.h"
#include "PunctuationTokenFactory.h"

shared_ptr<Token> PunctuationTokenFactory::createToken(std::string value) {
	return make_shared<PunctuationToken>(value);
}