#include "catch.hpp"
#include "qps/entity/parser/DeclarationsParser.h"
#include <common/spa_exception/SemanticErrorException.h>
#include <common/spa_exception/SyntaxErrorException.h>

//std::vector<std::shared_ptr<Synonym>> expectedDeclarations;

// ai-gen start (gpt, 1, e)
// Prompt: https://chat.openai.com/share/82e2cd52-da0f-49d9-8032-25cca59e34b3
TEST_CASE("Valid Declarations", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "variable", "a", ",", "b", ",", "x", ";" };
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
	std::vector<std::string> tokens = { "variable", "a", ";" };
	std::unordered_map<std::string, EntityType> synonymMap = {};
	auto declarations = DeclarationsParser::parse(tokens, synonymMap);

    REQUIRE(declarations[0].get()->getName() == "a");
    REQUIRE(declarations[0].get()->getType() == EntityType::Variable);
	REQUIRE(declarations.size() == 1);
	REQUIRE(synonymMap.find("a") != synonymMap.end());
}

TEST_CASE("Invalid First Token", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "InvalidType", "a", ";" };
	std::unordered_map<std::string, EntityType> synonymMap = { {"Variable", EntityType::Variable} };

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}

TEST_CASE("Duplicate Names", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "while", "a", ",", "a", ";" };
	std::unordered_map<std::string, EntityType> synonymMap = { {"Variable", EntityType::Variable} };

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SemanticErrorException);
}
// ai-gen end

// ai-gen start (gpt, 0, e)
// prompt: https://chat.openai.com/share/d86b9515-ec39-46ef-aaae-c8e284de92a2
TEST_CASE("Consecutive Commas Without Synonym Name", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "if", "a", ",", ",", ",", ",", "b", ";" };
	std::unordered_map<std::string, EntityType> synonymMap;

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}

TEST_CASE("Non-Separated Synonym Names", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "procedure", "a", "b", "c", ";" };
	std::unordered_map<std::string, EntityType> synonymMap;

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}

TEST_CASE("Numeric Synonym Names", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "constant", "1", "2", ";" };
	std::unordered_map<std::string, EntityType> synonymMap;

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}
// ai-gen end

TEST_CASE("Invalid Synonym Names", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "stmt", "123lolol", "_invalid_", ";" };
	std::unordered_map<std::string, EntityType> synonymMap;

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}

TEST_CASE("Tokens end expecting variable names", "[DeclarationParser]") {
    DeclarationsParser parser;
    std::vector<std::string> tokens = {"read", "a", ",", ";"};
    std::unordered_map<std::string, EntityType> synonymMap;

    REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}

// Private method
/*TEST_CASE("mapTokenToEntityType Tests", "[DeclarationsParser]") {}*/
