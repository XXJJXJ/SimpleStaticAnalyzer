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
	auto declarations = parser.parse(tokens, synonymMap);

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
	auto declarations = parser.parse(tokens, synonymMap);

	REQUIRE(declarations.size() == 1);
	REQUIRE(synonymMap.find("a") != synonymMap.end());
}

TEST_CASE("Empty Tokens", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = {}; // Empty tokens
	std::unordered_map<std::string, EntityType> synonymMap = { {"Variable", EntityType::Variable} };

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}

TEST_CASE("Invalid First Token", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "InvalidType", "a", ";" };
	std::unordered_map<std::string, EntityType> synonymMap = { {"Variable", EntityType::Variable} };

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}

TEST_CASE("Duplicate Names", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "Variable", "a", ",", "a", ";" };
	std::unordered_map<std::string, EntityType> synonymMap = { {"Variable", EntityType::Variable} };

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}
// ai-gen end

// ai-gen start (gpt, 0, e)
// prompt:
TEST_CASE("Consecutive Commas Without Synonym Name", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "variable", "a", ",", ",", ",", ",", "b", ";" };
	std::unordered_map<std::string, EntityType> synonymMap;

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}

TEST_CASE("Non-Separated Synonym Names", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "variable", "a", "b", "c", ";" };
	std::unordered_map<std::string, EntityType> synonymMap;

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}

TEST_CASE("Numeric Synonym Names", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "variable", "1", "2", ";" };
	std::unordered_map<std::string, EntityType> synonymMap;

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}
// ai-gen end

TEST_CASE("Invalid Synonym Names", "[DeclarationsParser]") {
	DeclarationsParser parser;
	std::vector<std::string> tokens = { "variable", "123lolol", "_invalid_", ";" };
	std::unordered_map<std::string, EntityType> synonymMap;

	REQUIRE_THROWS_AS(parser.parse(tokens, synonymMap), SyntaxErrorException);
}

// ai-gen start (gpt, 2, e)
// prompt: https://chat.openai.com/share/4961f207-6946-4c80-8a64-e51b06b24aa1
TEST_CASE("mapTokenToEntityType Tests", "[DeclarationsParser]") {
	DeclarationsParser parser;

	REQUIRE(parser.mapTokenToEntityType("stmt") == EntityType::Stmt);
	REQUIRE(parser.mapTokenToEntityType("read") == EntityType::Read);
	REQUIRE(parser.mapTokenToEntityType("print") == EntityType::Print);
	REQUIRE(parser.mapTokenToEntityType("call") == EntityType::Call);
	REQUIRE(parser.mapTokenToEntityType("while") == EntityType::While);
	REQUIRE(parser.mapTokenToEntityType("if") == EntityType::If);
	REQUIRE(parser.mapTokenToEntityType("assign") == EntityType::Assign);
	REQUIRE(parser.mapTokenToEntityType("variable") == EntityType::Variable);
	REQUIRE(parser.mapTokenToEntityType("constant") == EntityType::Constant);
	REQUIRE(parser.mapTokenToEntityType("procedure") == EntityType::Procedure);
	REQUIRE(parser.mapTokenToEntityType("unknown_token") == EntityType::Unknown);
}
// ai-gen end