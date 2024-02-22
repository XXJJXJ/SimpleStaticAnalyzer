#include "catch.hpp"
#include "qps/QueryParser.h"
#include "qps/entity/parser/SelectionsParser.h"
#include "qps/entity/parser/PredicateFactory.h"
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

TEST_CASE("PredicateFactory successfully creates predicate objects") {
	PredicateFactory pf;
	std::unordered_map<std::string, EntityType> synonymMap;
	synonymMap["a"] = EntityType::Stmt;
	synonymMap["b"] = EntityType::Stmt;
	synonymMap["c"] = EntityType::Variable;
	

	SECTION("Testing successful creation of each type of predicate") {
		std::vector<std::string> tokens1 = { "Follows", "(", "a", ",", "b", ")" };
		std::vector<std::string> tokens2 = { "Follows*", "(", "a", ",", "b", ")" };
		std::vector<std::string> tokens3 = { "Modifies", "(", "a", ",", "c", ")" };
		std::vector<std::string> tokens4 = { "Parent", "(", "a", ",", "b", ")" };
		std::vector<std::string> tokens5 = { "Parent*", "(", "a", ",", "b", ")" };
		std::vector<std::string> tokens6 = { "Uses", "(", "a", ",", "c", ")" };
		std::vector<std::string> tokens7 = { "Relationship", "(", "a", ",", "b", ")" };

		REQUIRE_NOTHROW(pf.createPredicate(tokens1, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens2, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens3, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens4, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens5, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens6, synonymMap));
		REQUIRE_THROWS(pf.createPredicate(tokens7, synonymMap));
	}

	// Applies to Follows, Follows*, Parent, Parent*, because they all have StatementRef as lhs and rhs. The actual validity of input is already tested in TestPredicateConstructors
	SECTION("Testing different input types for StatementRef") {
		std::vector<std::string> tokens1 = { "Follows", "(", "a", ",", "b", ")" }; //Valid synonyms
		std::vector<std::string> tokens2 = { "Follows*", "(", "_", ",", "b", ")" }; //Valid synonym + wildcard
		std::vector<std::string> tokens3 = { "Parent", "(", "1", ",", "b", ")" }; //Valid synonym + integer
		std::vector<std::string> tokens4 = { "Parent*", "(", "a", ",", "c", ")" }; //Invalid synonym type
		std::vector<std::string> tokens5 = { "Follows", "(", "01", ",", "b", ")" }; //Invalid integer
		std::vector<std::string> tokens6 = { "Follows", "(", "a", ",", "\"b\"", ")" }; //String (invalid)

		REQUIRE_NOTHROW(pf.createPredicate(tokens1, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens2, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens3, synonymMap));
		REQUIRE_THROWS(pf.createPredicate(tokens4, synonymMap));
		REQUIRE_THROWS(pf.createPredicate(tokens5, synonymMap));
		REQUIRE_THROWS(pf.createPredicate(tokens6, synonymMap));
	}

	// Applies to rhs of Modifies and Uses. Lhs is ignored since input type is essentially == StatementRef. Once again actuall validity already tested in TestPredicateConstructors
	SECTION("Testing different input types for EntityRef") {
		std::vector<std::string> tokens1 = { "Modifies", "(", "a", ",", "c", ")" }; //Valid synonyms
		std::vector<std::string> tokens2 = { "Uses", "(", "a", ",", "_", ")" }; //Valid synonym + wildcard
		std::vector<std::string> tokens3 = { "Modifies", "(", "a", ",", "\"b\"", ")" }; //Valid synonym + string (valid)
		std::vector<std::string> tokens4 = { "Uses", "(", "a", ",", "b", ")" }; //Invalid synonym type
		std::vector<std::string> tokens5 = { "Modifies", "(", "a", ",", "1", ")" }; //Integer (invalid)

		REQUIRE_NOTHROW(pf.createPredicate(tokens1, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens2, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens3, synonymMap));
		REQUIRE_THROWS(pf.createPredicate(tokens4, synonymMap));
		REQUIRE_THROWS(pf.createPredicate(tokens5, synonymMap));
	}
}