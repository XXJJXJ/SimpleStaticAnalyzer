#include "Tokenizer.h"

std::vector<shared_ptr<Token>> Tokenizer::tokenize(std::ifstream& file) {
	std::regex token_regex(R"(\bprocedure\b|\bwhile\b|\bif\b|\bthen\b|\belse\b|\bcall\b|\bread\b|\bprint\b|\btrue\b|\bfalse\b|[a-zA-Z][a-zA-Z0-9]*|[0-9]+|\+|-|\*|/|%|==|!=|<|<=|>|>=|\(|\)|\{|\}|\;|\=)");
	std::vector<shared_ptr<Token>> tokens;

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
	if (value == "(" || value == ")" || value == "{" || value == ";" || value == "\"") {
		return PunctuationTokenFactory::createToken(value);
	}
	else {
		return NameTokenFactory::createToken(value);
	}
}
