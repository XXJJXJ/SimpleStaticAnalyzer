#pragma once

#include "TokenFactory.h"

class NameTokenFactory : public TokenFactory {
 public:
  static shared_ptr<Token> createToken(std::string value);
};