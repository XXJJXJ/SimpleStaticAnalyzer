#include "catch.hpp"
#include "qps/QueryParser.h"
#include "qps/QueryTokenizer.h"
#include "qps/QueryEvaluator.h"
#include "qps/entity/evaluation/EvaluationPlanner.h"
#include "qps/entity/parser/SelectionsParser.h"
#include "qps/entity/parser/PredicateFactory.h"
#include "common/spa_exception/SemanticErrorException.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "fakeEntities/FakeQueryManager.cpp"
#include "sp/SP.h"

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

TEST_CASE("PredicateFactory::createPredicate successfully creates predicate objects") {
	PredicateFactory pf;
	std::unordered_map<std::string, EntityType> synonymMap;
	synonymMap["a"] = EntityType::Stmt;
	synonymMap["b"] = EntityType::Stmt;
	synonymMap["c"] = EntityType::Variable;
	synonymMap["d"] = EntityType::Assign;
	

	SECTION("Testing successful creation of each type of predicate") {
		std::vector<std::string> tokens1 = { "Follows", "(", "a", ",", "b", ")" };
		std::vector<std::string> tokens2 = { "Follows*", "(", "a", ",", "b", ")" };
		std::vector<std::string> tokens3 = { "Modifies", "(", "a", ",", "c", ")" };
		std::vector<std::string> tokens4 = { "Parent", "(", "a", ",", "b", ")" };
		std::vector<std::string> tokens5 = { "Parent*", "(", "a", ",", "b", ")" };
		std::vector<std::string> tokens6 = { "Uses", "(", "a", ",", "c", ")" };
		std::vector<std::string> tokens7 = { "pattern", "d", "(", "c", ",", "_", ")"};
		std::vector<std::string> tokens8 = { "Relationship", "(", "a", ",", "b", ")" };

		REQUIRE_NOTHROW(pf.createPredicate(tokens1, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens2, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens3, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens4, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens5, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens6, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens7, synonymMap));
		REQUIRE_THROWS(pf.createPredicate(tokens8, synonymMap));
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

	// Applies to rhs of Modifies and Uses. Lhs is ignored since input type is essentially == StatementRef. 
	// Also applies to lhs of AssignPattern
	// Once again actuall validity already tested in TestPredicateConstructors
	SECTION("Testing different input types for EntityRef") {
		std::vector<std::string> tokens1 = { "Modifies", "(", "a", ",", "c", ")" }; //Valid synonyms
		std::vector<std::string> tokens2 = { "Uses", "(", "a", ",", "_", ")" }; //Valid synonym + wildcard
		std::vector<std::string> tokens3 = { "Modifies", "(", "a", ",", "\"b\"", ")" }; //Valid synonym + string (valid)
		std::vector<std::string> tokens4 = { "Uses", "(", "a", ",", "b", ")" }; //Invalid synonym type
		std::vector<std::string> tokens5 = { "pattern", "d", "(", "1", ",", "_", ")"}; //Integer (invalid)
		std::vector<std::string> tokens6 = { "Uses", "(", "\"a\"", ",", "c", ")" }; //Ident name for lhs (valid)

		REQUIRE_NOTHROW(pf.createPredicate(tokens1, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens2, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens3, synonymMap));
		REQUIRE_THROWS(pf.createPredicate(tokens4, synonymMap));
		REQUIRE_THROWS(pf.createPredicate(tokens5, synonymMap));
		REQUIRE_NOTHROW(pf.createPredicate(tokens6, synonymMap));
	}
}

TEST_CASE("PredicateFactory::createPredicate should throw errors for invalid queries") {
	PredicateFactory pf;
	std::unordered_map<std::string, EntityType> synonymMap;
	synonymMap["a"] = EntityType::Stmt;
	synonymMap["b"] = EntityType::Stmt;
	synonymMap["c"] = EntityType::Variable;
	synonymMap["d"] = EntityType::Assign;

	std::vector<std::string> tokens1 = { "Modifies", "(", "a", ")" }; // Too few arguments
	std::vector<std::string> tokens2 = { "Follows", "(", "a", ",", "b", ",", "c", ")" }; // Too many arguments
	std::vector<std::string> tokens3 = { "Parent", "extraWord", "(", "a", ",", "b", ")" }; // Extra word before "("
	std::vector<std::string> tokens4 = { "Uses", "(", "a", ",", "_", ",", ")" }; // Invalid syntax in clause

	REQUIRE_THROWS(pf.createPredicate(tokens1, synonymMap));
	REQUIRE_THROWS(pf.createPredicate(tokens2, synonymMap));
	REQUIRE_THROWS(pf.createPredicate(tokens3, synonymMap));
	REQUIRE_THROWS(pf.createPredicate(tokens4, synonymMap));
}

TEST_CASE("Integration test") {
    auto sp = Sp();
    sp.ProcessSIMPLE("milestone1_modifiesp_usesp_call_source.txt");

    string query = "stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; procedure p, q; constant c; read re; print pn; call cl; Select a such that Parent(8,a)";
    QueryTokenizer qt;
    QueryParser qp;
    std::vector<std::vector<std::vector<std::string>>> tokens = qt.tokenize(query);
    REQUIRE_NOTHROW(qp.parse(tokens));
    auto q = qp.parse(tokens);
    auto qe = make_shared<QueryEvaluator>();

    EvaluationPlanner ep = EvaluationPlanner(q, qe);
    ep.plan();
    auto res = qe->evaluate(q);
    REQUIRE(res.size() == 3);

//    auto stmt1 = make_shared<Statement>(1, EntityType::Stmt ,"p");
//    auto stmt2 = make_shared<Statement>(2, EntityType::Call ,"p");
//    auto stmt3 = make_shared<Statement>(3, EntityType::Read ,"p");
//    auto stmt4 = make_shared<Statement>(4, EntityType::Print ,"p");
//    auto stmt5 = make_shared<Statement>(5, EntityType::While ,"p");
//    auto stmt6 = make_shared<Statement>(6, EntityType::If ,"p");
//    auto stmt7 = make_shared<Statement>(7, EntityType::Assign ,"p");
//    auto stmt8 = make_shared<Statement>(8, EntityType::Stmt ,"p");
//    auto stmt9 = make_shared<Statement>(9, EntityType::Stmt ,"p");
//
//    auto qm = make_shared<FakeQueryManager>();
//    qm->addFakeFollows(stmt1, stmt2);
//    qm->addFakeFollows(stmt2, stmt3);
//    qm->addFakeFollows(stmt3, stmt4);
//    qm->addFakeFollows(stmt4, stmt5);
//    qm->addFakeFollows(stmt5, stmt6);
//    qm->addFakeFollows(stmt6, stmt7);
//    qm->addFakeFollows(stmt7, stmt8);
//    qm->addFakeFollows(stmt8, stmt9);
//    qe->getContext()->setQueryManager(qm);



}