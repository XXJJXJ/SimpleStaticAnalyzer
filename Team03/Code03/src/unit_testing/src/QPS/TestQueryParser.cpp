#include "catch.hpp"
#include "qps/QueryParser.h"
#include "qps/entity/parser/SelectionsParser.h"
#include "qps/entity/parser/SuchThatClauseFactory.h"
#include "common/spa_exception/SemanticErrorException.h"
#include "common/spa_exception/SyntaxErrorException.h"

// fails for now because DeclarationsParser is not implemented yet
//TEST_CASE("QueryParser::parse should return a Query object") {
//	QueryParser qp;
//	std::vector<std::vector<std::vector<std::string>>> tokens = { {{"variable", "a", ";"}}, {{"Select", "a"}}, {{"such", "that", "Follows", "(", "a", ",", "_", ")"}, {"pattern", "a", "(", "_", ",", "_", ")"}} };
//	REQUIRE_NOTHROW(qp.parse(tokens));
//}

TEST_CASE("SelectionsParser::parse should correctly parse and return a vector of Synonym objects") {
	SelectionsParser sp;
	std::unordered_map<std::string, EntityType> synonymMap;
	synonymMap["a"] = EntityType::Variable;
	synonymMap["b"] = EntityType::Assign;

	std::vector<std::string> tokens1 = {"Select", "a"};
	std::vector<std::string> tokens2 = {"Select", "b"};
	std::vector<std::string> tokens3 = {"Select", "c"};
	std::vector<std::string> tokens4 = {"Select", "<", "a", ",", "b", ">"};
	std::vector<std::string> tokens5 = {"Select", "<", "a", ",", "c", ">"};
	std::vector<std::string> tokens6 = {"Select", "<", "a", "b", ">"};
	std::vector<std::string> tokens7 = { "Select", "<", "a", ",", "b", ",", ">" };

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

	REQUIRE_THROWS_AS(sp.parse(tokens6, synonymMap), SyntaxErrorException);

	REQUIRE_THROWS_AS(sp.parse(tokens7, synonymMap), SyntaxErrorException);
}

TEST_CASE("SuchThatClauseFactory successfully creates a such that clause") {
	SuchThatClauseFactory s;
	std::unordered_map<std::string, EntityType> synonymMap;
	synonymMap["a"] = EntityType::Stmt;
	synonymMap["b"] = EntityType::Stmt;
	synonymMap["c"] = EntityType::Variable;

	std::vector<std::string> tokens1 = { "such", "that", "Follows", "(", "a", ",", "b", ")"};
	std::vector<std::string> tokens2 = { "such", "that", "Follows*", "(", "a", ",", "b", ")" };
	std::vector<std::string> tokens3 = { "such", "that", "Modifies", "(", "a", ",", "c", ")" };
	std::vector<std::string> tokens4 = { "such", "that", "Parent", "(", "a", ",", "b", ")" };
	std::vector<std::string> tokens5 = { "such", "that", "Parent*", "(", "a", ",", "b", ")" };
	std::vector<std::string> tokens6 = { "such", "that", "Uses", "(", "a", ",", "c", ")" };
	std::vector<std::string> tokens7 = { "such", "that", "Relationship", "(", "a", ",", "b", ")" };
	

	REQUIRE_NOTHROW(s.createClauseObject(tokens1, synonymMap));
	REQUIRE_NOTHROW(s.createClauseObject(tokens2, synonymMap));
	REQUIRE_NOTHROW(s.createClauseObject(tokens3, synonymMap));
	REQUIRE_NOTHROW(s.createClauseObject(tokens4, synonymMap));
	REQUIRE_NOTHROW(s.createClauseObject(tokens5, synonymMap));
	REQUIRE_NOTHROW(s.createClauseObject(tokens6, synonymMap));
	REQUIRE_THROWS(s.createClauseObject(tokens7, synonymMap));
}