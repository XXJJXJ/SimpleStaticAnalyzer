#include "catch.hpp"
#include "qps/entity/parser/PredicateFactory.h"

TEST_CASE("PredicateFactory::createPredicate successfully creates predicate objects") {
    PredicateFactory pf;
    std::unordered_map<std::string, EntityType> synonymMap;
    synonymMap["a"] = EntityType::Stmt;
    synonymMap["b"] = EntityType::Stmt;
    synonymMap["c"] = EntityType::Variable;
    synonymMap["d"] = EntityType::Assign;
    synonymMap["e"] = EntityType::Procedure;
    synonymMap["f"] = EntityType::While;
    synonymMap["g"] = EntityType::If;

    std::vector<std::string> tokens1 = { "Follows", "a", "b" };
    std::vector<std::string> tokens2 = { "Follows*", "a", "b" };
    std::vector<std::string> tokens3 = { "Modifies", "a", "c" };
    std::vector<std::string> tokens4 = { "Parent", "a", "b" };
    std::vector<std::string> tokens5 = { "Parent*", "a", "b" };
    std::vector<std::string> tokens6 = { "Uses", "a", "c" };
    std::vector<std::string> tokens7 = { "Calls", "e", "e" };
    std::vector<std::string> tokens8 = { "Calls*", "e", "e" };
    std::vector<std::string> tokens9 = { "pattern", "d", "c", "_" };
    std::vector<std::string> tokens10 = { "pattern", "f", "_", "_" };
    std::vector<std::string> tokens11 = { "pattern", "g", "_", "_", "_" };
    std::vector<std::string> tokens12 = { "Next", "a", "b" };
    std::vector<std::string> tokens13 = { "Next*", "a", "b" };
    std::vector<std::string> tokens14 = { "Affects", "a", "b" };
    std::vector<std::string> tokens15 = {"with", "a.stmt#", "8"};

    REQUIRE_NOTHROW(pf.createPredicate(tokens1, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens2, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens3, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens4, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens5, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens6, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens7, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens8, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens9, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens10, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens11, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens12, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens13, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens14, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens15, synonymMap));
}

TEST_CASE("Invalid pattern predicates") {
    PredicateFactory pf;
    std::unordered_map<std::string, EntityType> synonymMap;
    synonymMap["a"] = EntityType::Assign;
    synonymMap["b"] = EntityType::While;
    synonymMap["c"] = EntityType::If;
    synonymMap["d"] = EntityType::Call;

    std::vector<std::string> tokens1 = { "pattern", "a", "_", "_", "_" }; // Assign pattern wrong number of arguments
    std::vector<std::string> tokens2 = { "pattern", "b", "_", "b" }; // While pattern RHS not wildcard
    std::vector<std::string> tokens3 = { "pattern", "b", "_", "_", "_" }; // While pattern wrong number of arguments 
    std::vector<std::string> tokens4 = { "pattern", "c", "_", "_" }; // If pattern wrong number of arguments
    std::vector<std::string> tokens5 = { "pattern", "d", "_", "_" }; // Invalid synonym type
    std::vector<std::string> tokens6 = { "pattern", "d", "_", "_", "_" }; // Invalid synonym type

    REQUIRE_THROWS_AS(pf.createPredicate(tokens1, synonymMap), SemanticErrorException);
    REQUIRE_THROWS_AS(pf.createPredicate(tokens2, synonymMap), SemanticErrorException);
    REQUIRE_THROWS_AS(pf.createPredicate(tokens3, synonymMap), SemanticErrorException);
    REQUIRE_THROWS_AS(pf.createPredicate(tokens4, synonymMap), SemanticErrorException);
    REQUIRE_THROWS_AS(pf.createPredicate(tokens5, synonymMap), SemanticErrorException);
    REQUIRE_THROWS_AS(pf.createPredicate(tokens6, synonymMap), SemanticErrorException);
}

TEST_CASE("WithPredicate semantic validation") {
    std::unordered_map<std::string, EntityType> synonymMap;
    synonymMap["a"] = EntityType::Procedure; // valid for procName
    synonymMap["b"] = EntityType::Variable; // valid for varName
    synonymMap["c"] = EntityType::Constant; // valid for value
    synonymMap["d"] = EntityType::While; // valid for stmt#
    std::string VALID_NAME = "\"validName\"";
    std::string VALID_NAME1 = "\"validName\"";

    SECTION("Valid WithPredicates") {
        std::vector<std::string> tokens1 = {"with", "a.procName", VALID_NAME};
        std::vector<std::string> tokens2 = {"with", VALID_NAME, "b.varName"};
        std::vector<std::string> tokens3 = {"with", "c.value", "8"};
        std::vector<std::string> tokens4 = {"with", "8", "d.stmt#"};
        std::vector<std::string> tokens5 = {"with", "8", "8"};
        std::vector<std::string> tokens6 = {"with", "a.procName", "b.varName"};
        std::vector<std::string> tokens7 = {"with", VALID_NAME, VALID_NAME1};

        REQUIRE_NOTHROW(PredicateFactory::createPredicate(tokens1, synonymMap));
        REQUIRE_NOTHROW(PredicateFactory::createPredicate(tokens2, synonymMap));
        REQUIRE_NOTHROW(PredicateFactory::createPredicate(tokens3, synonymMap));
        REQUIRE_NOTHROW(PredicateFactory::createPredicate(tokens4, synonymMap));
        REQUIRE_NOTHROW(PredicateFactory::createPredicate(tokens5, synonymMap));
        REQUIRE_NOTHROW(PredicateFactory::createPredicate(tokens6, synonymMap));
        REQUIRE_NOTHROW(PredicateFactory::createPredicate(tokens7, synonymMap));
    }

    SECTION("Invalid WithPredicates") {
        std::vector<std::string> tokens1 = {"with", "a.procName", "8"}; // compare name with integer
        std::vector<std::string> tokens2 = {"with", "8", "b.varName"}; // compare integer with name
        std::vector<std::string> tokens3 = {"with", "c.value", VALID_NAME}; // compare integer with name
        std::vector<std::string> tokens4 = {"with", VALID_NAME, "d.stmt#"}; // compare name with integer
        std::vector<std::string> tokens5 = {"with", "b.procName", VALID_NAME}; // invalid synonym type for procName
        std::vector<std::string> tokens6 = {"with", VALID_NAME, "a.varName"}; // invalid synonym type for varName
        std::vector<std::string> tokens7 = {"with", "d.value", "8"}; // invalid synonym type for value
        std::vector<std::string> tokens8 = {"with", "8", "b.stmt#"}; // invalid synonym type for stmt#
        std::vector<std::string> tokens9 = {"with", "e.procName", VALID_NAME}; // undeclared synonym

        REQUIRE_THROWS_AS(PredicateFactory::createPredicate(tokens1, synonymMap), SemanticErrorException);
        REQUIRE_THROWS_AS(PredicateFactory::createPredicate(tokens2, synonymMap), SemanticErrorException);
        REQUIRE_THROWS_AS(PredicateFactory::createPredicate(tokens3, synonymMap), SemanticErrorException);
        REQUIRE_THROWS_AS(PredicateFactory::createPredicate(tokens4, synonymMap), SemanticErrorException);
        REQUIRE_THROWS_AS(PredicateFactory::createPredicate(tokens5, synonymMap), SemanticErrorException);
        REQUIRE_THROWS_AS(PredicateFactory::createPredicate(tokens6, synonymMap), SemanticErrorException);
        REQUIRE_THROWS_AS(PredicateFactory::createPredicate(tokens7, synonymMap), SemanticErrorException);
        REQUIRE_THROWS_AS(PredicateFactory::createPredicate(tokens8, synonymMap), SemanticErrorException);
        REQUIRE_THROWS_AS(PredicateFactory::createPredicate(tokens9, synonymMap), SemanticErrorException);
    }
}