#pragma once

#include "TokenFactory.h"

class ArithmeticTokenFactory : public TokenFactory {
 public:
  static shared_ptr<Token> createToken(std::string value);
};