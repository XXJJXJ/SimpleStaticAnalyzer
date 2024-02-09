#include "NameToken.h"
#include "NameTokenFactory.h"

Token NameTokenFactory::createToken(std::string value) { return NameToken(value); }