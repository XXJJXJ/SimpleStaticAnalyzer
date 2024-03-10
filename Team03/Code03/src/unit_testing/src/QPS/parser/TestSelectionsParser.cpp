#include "catch.hpp"
#include "qps/entity/parser/SelectionsParser.h"
#include "common/spa_exception/SemanticErrorException.h"

TEST_CASE("SelectionsParser::parse should correctly parse and return a vector of Synonym objects") {
	SelectionsParser sp;
	std::unordered_map<std::string, EntityType> synonymMap;
	synonymMap["a"] = EntityType::Variable;
	synonymMap["b"] = EntityType::Assign;

	SECTION("Valid selections") {
		std::vector<std::string> tokens1 = { "a" };
		std::vector<std::string> tokens2 = { "b" };
		std::vector<std::string> tokens3 = { "a", "b" };

		std::vector<std::shared_ptr<Synonym>> results1 = sp.parse(tokens1, synonymMap);
		std::vector<std::shared_ptr<Synonym>> results2 = sp.parse(tokens2, synonymMap);
		std::vector<std::shared_ptr<Synonym>> results3 = sp.parse(tokens3, synonymMap);

		REQUIRE(results1.size() == 1);
		REQUIRE(results1[0]->getName() == "a");
		REQUIRE(results1[0]->getType() == EntityType::Variable);

		REQUIRE(results2.size() == 1);
		REQUIRE(results2[0]->getName() == "b");
		REQUIRE(results2[0]->getType() == EntityType::Assign);

		REQUIRE(results3.size() == 2);
		REQUIRE(results3[0]->getName() == "a");
		REQUIRE(results3[0]->getType() == EntityType::Variable);
		REQUIRE(results3[1]->getName() == "b");
		REQUIRE(results3[1]->getType() == EntityType::Assign);
	}

	SECTION("Semantically invalid selections") {
		std::vector<std::string> tokens1 = { "c" }; // Undeclared variable
		std::vector<std::string> tokens2 = { "a", "c" }; // Undeclared variable

		REQUIRE_THROWS_AS(sp.parse(tokens1, synonymMap), SemanticErrorException);
		REQUIRE_THROWS_AS(sp.parse(tokens2, synonymMap), SemanticErrorException);
	}
}