#include "../Token/ConditionalToken.h"
#include "ConditionalTokenFactory.h"

shared_ptr<Token> ConditionalTokenFactory::createToken(std::string value) {
    return make_shared<ConditionalToken>(value);
}