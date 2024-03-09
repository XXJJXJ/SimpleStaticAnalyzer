#include "catch.hpp"
#include "qps/QueryParser.h"
#include "qps/entity/parser/SelectionsParser.h"
#include "qps/entity/parser/PredicateFactory.h"
#include "common/spa_exception/SemanticErrorException.h"


TEST_CASE("QueryParser::parse should return a Query object") {
	QueryParser qp;
	std::vector<std::vector<std::vector<std::string>>> tokens = { {{"stmt", "s"}, {"assign", "a"}}, {{"s"}}, {{"Follows", "s", "_"}, {"pattern", "a", "_", "_"}} };
	REQUIRE_NOTHROW(qp.parse(tokens));
	std::vector<std::vector<std::vector<std::string>>> tokens2 = { {{"constant", "c"}}, {{"c"}}, {} };
    REQUIRE_NOTHROW(qp.parse(tokens2));
}

TEST_CASE("SelectionsParser::parse should correctly parse and return a vector of Synonym objects") {
	SelectionsParser sp;
	std::unordered_map<std::string, EntityType> synonymMap;
	synonymMap["a"] = EntityType::Variable;
	synonymMap["b"] = EntityType::Assign;

	std::vector<std::string> tokens1 = {"a"};
	std::vector<std::string> tokens2 = {"b"};
	std::vector<std::string> tokens3 = {"c"}; // Undeclared variable
	std::vector<std::string> tokens4 = {"a", "b"};
	std::vector<std::string> tokens5 = {"a", "c"}; // Undeclared variable

	std::vector<std::shared_ptr<Synonym>> results1 = sp.parse(tokens1, synonymMap);
	std::vector<std::shared_ptr<Synonym>> results2 = sp.parse(tokens2, synonymMap);
	std::vector<std::shared_ptr<Synonym>> results4 = sp.parse(tokens4, synonymMap);

	REQUIRE(results1.size() == 1);
	REQUIRE(results1[0]->getName() == "a");
	REQUIRE(results1[0]->getType() == EntityType::Variable);

	REQUIRE(results2.size() == 1);
	REQUIRE(results2[0]->getName() == "b");
	REQUIRE(results2[0]->getType() == EntityType::Assign);

	REQUIRE_THROWS_AS(sp.parse(tokens3, synonymMap), SemanticErrorException);

	REQUIRE(results4.size() == 2);
	REQUIRE(results4[0]->getName() == "a");
	REQUIRE(results4[0]->getType() == EntityType::Variable);
	REQUIRE(results4[1]->getName() == "b");
	REQUIRE(results4[1]->getType() == EntityType::Assign);

	REQUIRE_THROWS_AS(sp.parse(tokens5, synonymMap), SemanticErrorException);
}

TEST_CASE("PredicateFactory::createPredicate successfully creates predicate objects") {
	PredicateFactory pf;
	std::unordered_map<std::string, EntityType> synonymMap;
	synonymMap["a"] = EntityType::Stmt;
	synonymMap["b"] = EntityType::Stmt;
	synonymMap["c"] = EntityType::Variable;
	synonymMap["d"] = EntityType::Assign;

    std::vector<std::string> tokens1 = { "Follows", "a", "b"};
    std::vector<std::string> tokens2 = { "Follows*", "a", "b"};
    std::vector<std::string> tokens3 = { "Modifies", "a", "c" };
    std::vector<std::string> tokens4 = { "Parent", "a", "b" };
    std::vector<std::string> tokens5 = { "Parent*", "a", "b" };
    std::vector<std::string> tokens6 = { "Uses", "a", "c" };
    std::vector<std::string> tokens7 = { "pattern", "d", "c", "_"};

    REQUIRE_NOTHROW(pf.createPredicate(tokens1, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens2, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens3, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens4, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens5, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens6, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens7, synonymMap));
}