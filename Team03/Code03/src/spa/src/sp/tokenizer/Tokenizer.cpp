#include "Tokenizer.h"

Tokens Tokenizer::tokenize(std::ifstream& file) {
	std::regex token_regex(R"(\bprocedure\b|\bwhile\b|\bif\b|\bthen\b|\belse\b|\bcall\b|\bread\b|\bprint\b|\btrue\b|\bfalse\b|\+|-|\*|/|%|==|!=|<|<=|>|>=|\(|\)|\{|\}|;|\=|\"|&&|\|\||!|((?!;)[a-zA-Z0-9]+))");
	Tokens tokens;

	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::sregex_iterator iter(line.begin(), line.end(), token_regex);
			std::sregex_iterator end;

			while (iter != end) {
				tokens.push_back(stringToToken(iter->str()));
				++iter;
			}
		}
	}
	return tokens;
}

shared_ptr<Token> Tokenizer::stringToToken(std::string value) {
	std::regex name_regex(R"((?!;)[a-zA-Z0-9]+))");

	if (value == "(" || value == ")" || value == "{" || value == "}" || value == ";" || value == "\"") {
		return PunctuationTokenFactory::createToken(value);
	}
	else if (isdigit(value[0])) {
		for (int i = 1; i < value.size(); i++) {
			if (!isdigit(value[i])) {
				return TokenFactory::createToken(value);
			}
		}
		return IntegerTokenFactory::createToken(value);
	}
	else if (value == "=" | value == "+" | value == "-" | value == "*" | value == "/" | value == "%") {
		return ArithmeticTokenFactory::createToken(value);
	}
	else if (value == "<" | value == "<=" | value == ">" | value == ">=" | value == "==" | value == "!=") {
		return RelationalTokenFactory::createToken(value);
	}
	else if (value == "&&" | value == "||" | value == "!") {
		return ConditionalTokenFactory::createToken(value);
	}
	else if (std::regex_match(value, name_regex)) {
		return NameTokenFactory::createToken(value);
	}
	else {
		return TokenFactory::createToken(value);
	}
}
