#include "catch.hpp"
#include "qps/entity/parser/DeclarationsParser.h"
#include <common/spa_exception/SemanticErrorException.h>
#include <common/spa_exception/SyntaxErrorException.h>

//std::vector<std::shared_ptr<Synonym>> expectedDeclarations;

// ai-gen start (gpt, 1, e)
// Prompt: https://chat.openai.com/share/82e2cd52-da0f-49d9-8032-25cca59e34b3
TEST_CASE("Valid Declarations", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "variable", "a", "b", "x"};
	std::unordered_map<std::string, EntityType> synonymMap = {};
	auto declarations = DeclarationsParser::parse(tokens, synonymMap);

	REQUIRE(declarations.size() == 3);
	REQUIRE(synonymMap.size() == 3);

	REQUIRE(synonymMap["a"] == EntityType::Variable);
	REQUIRE(synonymMap["b"] == EntityType::Variable);
	REQUIRE(synonymMap["x"] == EntityType::Variable);
}

TEST_CASE("Single Declaration", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "variable", "a" };
	std::unordered_map<std::string, EntityType> synonymMap = {};
	auto declarations = DeclarationsParser::parse(tokens, synonymMap);

    REQUIRE(declarations[0].get()->getName() == "a");
    REQUIRE(declarations[0].get()->getType() == EntityType::Variable);
	REQUIRE(declarations.size() == 1);
	REQUIRE(synonymMap.find("a") != synonymMap.end());
}

TEST_CASE("Duplicate Names", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "while", "a", "a" };
	std::unordered_map<std::string, EntityType> synonymMap = { {"Variable", EntityType::Variable} };

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SemanticErrorException);
}
// ai-gen end