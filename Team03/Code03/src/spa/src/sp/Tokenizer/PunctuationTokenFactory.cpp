#include "PunctuationToken.h"
#include "PunctuationTokenFactory.h"

Token PunctuationTokenFactory::createToken(std::string value) { return PunctuationToken(value); }