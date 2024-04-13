#pragma once

#include "OperationParser.h"
#include "common/expression/ArithmeticOperation.h"
#include "common/expression/Constant.h"
#include "common/expression/Variable.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "../tokenizer/Token/Token.h"
#include "unordered_set"

using namespace std;

class ArithmeticOperationParser : public OperationParser {
 public:
  shared_ptr<Expression> parse() override;

 private:
  unordered_set<TokenType> termOperators = {TokenType::PLUS, TokenType::MINUS};
  unordered_set<TokenType> factorOperators = {TokenType::TIMES, TokenType::DIVIDE, TokenType::MODULUS};
  bool checkTermFactorOperators(bool isTerm, TokenType tokenType);
  shared_ptr<Expression> parseTermExpression();
  shared_ptr<Expression> parseExpression(bool isTerm);
  shared_ptr<Expression> parseFactorExpression();
  shared_ptr<Expression> parseLeafExpression(TokenType tokenType);
};