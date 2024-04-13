#include "../Token/ArithmeticToken.h"
#include "ArithmeticTokenFactory.h"

shared_ptr<Token> ArithmeticTokenFactory::createToken(std::string value) {
    return make_shared<ArithmeticToken>(value);
}