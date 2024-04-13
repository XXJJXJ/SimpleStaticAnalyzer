#pragma once

#include "Token.h"

class NameToken : public Token {
 public:
  NameToken(std::string value);
};