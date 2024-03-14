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
}

TEST_CASE("Invalid pattern predicates") {
    PredicateFactory pf;
    std::unordered_map<std::string, EntityType> synonymMap;
    synonymMap["a"] = EntityType::Assign;
    synonymMap["b"] = EntityType::While;
    synonymMap["c"] = EntityType::If;
    synonymMap["d"] = EntityType::Call;

    std::vector<std::string> tokens1 = { "pattern", "a", "c", "1()x" }; // Assign pattern invalid RHS
    std::vector<std::string> tokens2 = { "pattern", "a", "_", "_", "_" }; // Assign pattern wrong number of arguments
    std::vector<std::string> tokens3 = { "pattern", "b", "_", "b" }; // While pattern RHS not wildcard
    std::vector<std::string> tokens4 = { "pattern", "b", "_", "_", "_" }; // While pattern wrong number of arguments 
    std::vector<std::string> tokens5 = { "pattern", "c", "_", "_" }; // If pattern wrong number of arguments
    std::vector<std::string> tokens6 = { "pattern", "d", "_", "_" }; // Invalid synonym type
    std::vector<std::string> tokens7 = { "pattern", "d", "_", "_", "_" }; // Invalid synonym type

    REQUIRE_THROWS_AS(pf.createPredicate(tokens1, synonymMap), SyntaxErrorException);
    REQUIRE_THROWS_AS(pf.createPredicate(tokens2, synonymMap), SyntaxErrorException);
    REQUIRE_THROWS_AS(pf.createPredicate(tokens3, synonymMap), SyntaxErrorException);
    REQUIRE_THROWS_AS(pf.createPredicate(tokens4, synonymMap), SyntaxErrorException);
    REQUIRE_THROWS_AS(pf.createPredicate(tokens5, synonymMap), SyntaxErrorException);
    REQUIRE_THROWS_AS(pf.createPredicate(tokens6, synonymMap), SemanticErrorException);
    REQUIRE_THROWS_AS(pf.createPredicate(tokens7, synonymMap), SemanticErrorException);
}