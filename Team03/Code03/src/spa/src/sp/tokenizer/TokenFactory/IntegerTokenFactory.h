#pragma once

#include "TokenFactory.h"

class IntegerTokenFactory : public TokenFactory {
 public:
  static shared_ptr<Token> createToken(std::string value);
};