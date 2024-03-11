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

    std::vector<std::string> tokens1 = { "Follows", "a", "b" };
    std::vector<std::string> tokens2 = { "Follows*", "a", "b" };
    std::vector<std::string> tokens3 = { "Modifies", "a", "c" };
    std::vector<std::string> tokens4 = { "Parent", "a", "b" };
    std::vector<std::string> tokens5 = { "Parent*", "a", "b" };
    std::vector<std::string> tokens6 = { "Uses", "a", "c" };
    std::vector<std::string> tokens7 = { "Calls", "e", "e" };
    std::vector<std::string> tokens8 = { "Calls*", "e", "e" };
    std::vector<std::string> tokens9 = { "pattern", "d", "c", "_" };

    REQUIRE_NOTHROW(pf.createPredicate(tokens1, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens2, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens3, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens4, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens5, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens6, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens7, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens8, synonymMap));
    REQUIRE_NOTHROW(pf.createPredicate(tokens9, synonymMap));
}