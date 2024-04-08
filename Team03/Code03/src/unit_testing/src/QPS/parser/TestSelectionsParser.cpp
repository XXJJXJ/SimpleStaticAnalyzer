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
		std::vector<std::string> tokens4 = { "BOOLEAN" };

		std::vector<std::shared_ptr<AttrRef>> results1 = sp.parse(tokens1, synonymMap);
		std::vector<std::shared_ptr<AttrRef>> results2 = sp.parse(tokens2, synonymMap);
		std::vector<std::shared_ptr<AttrRef>> results3 = sp.parse(tokens3, synonymMap);
		std::vector<std::shared_ptr<AttrRef>> results4 = sp.parse(tokens4, synonymMap);

		REQUIRE(results1.size() == 1);
		REQUIRE(results1[0]->getSynonym()->getName() == "a");
		REQUIRE(results1[0]->getSynonym()->getType() == EntityType::Variable);

		REQUIRE(results2.size() == 1);
		REQUIRE(results2[0]->getSynonym()->getName() == "b");
		REQUIRE(results2[0]->getSynonym()->getType() == EntityType::Assign);

		REQUIRE(results3.size() == 2);
		REQUIRE(results3[0]->getSynonym()->getName() == "a");
		REQUIRE(results3[0]->getSynonym()->getType() == EntityType::Variable);
		REQUIRE(results3[1]->getSynonym()->getName() == "b");
		REQUIRE(results3[1]->getSynonym()->getType() == EntityType::Assign);

		REQUIRE(results4.empty());
	}

	SECTION("Ambiguous BOOLEAN") {
		synonymMap["BOOLEAN"] = EntityType::Call;
		
		std::vector<std::string> tokens1 = { "BOOLEAN" };
		std::vector<std::string> tokens2 = { "a", "BOOLEAN" }; // Undeclared variable

		std::vector<std::shared_ptr<AttrRef>> results1 = sp.parse(tokens1, synonymMap);
		std::vector<std::shared_ptr<AttrRef>> results2 = sp.parse(tokens2, synonymMap);
		
		REQUIRE(results1.size() == 1);
		REQUIRE(results1[0]->getSynonym()->getName() == "BOOLEAN");
		REQUIRE(results1[0]->getSynonym()->getType() == EntityType::Call);

		REQUIRE(results2.size() == 2);
		REQUIRE(results2[0]->getSynonym()->getName() == "a");
		REQUIRE(results2[0]->getSynonym()->getType() == EntityType::Variable);
		REQUIRE(results2[1]->getSynonym()->getName() == "BOOLEAN");
		REQUIRE(results2[1]->getSynonym()->getType() == EntityType::Call);
	}

	SECTION("Semantically invalid selections") {
		std::vector<std::string> tokens1 = { "c" }; // Undeclared variable
		std::vector<std::string> tokens2 = { "a", "c" }; // Undeclared variable
		std::vector<std::string> tokens3 = { "a", "BOOLEAN" }; // Undeclared variable

		REQUIRE_THROWS_AS(sp.parse(tokens1, synonymMap), SemanticErrorException);
		REQUIRE_THROWS_AS(sp.parse(tokens2, synonymMap), SemanticErrorException);
		REQUIRE_THROWS_AS(sp.parse(tokens3, synonymMap), SemanticErrorException);
	}
}