// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "catch.hpp"
#include "qps/entity/query/Synonym.h"
#include "qps/entity/clause/ModifiesPredicate.h"
#include "qps/entity/clause/UsesPredicate.h"
#include "qps/entity/clause/FollowsPredicate.h"
#include "qps/entity/clause/FollowsTPredicate.h"
#include "qps/entity/clause/ParentPredicate.h"
#include "qps/entity/clause/ParentTPredicate.h"
#include "qps/entity/clause/AssignPatternPredicate.h"

TEST_CASE("Predicates Input Validations", "[Predicates]") {
    Synonym stmtSyn(EntityType::Stmt, "s1");
    Synonym stmtSyn2(EntityType::Stmt, "s2");
    Synonym varSyn(EntityType::Variable, "v");
    Synonym procSyn(EntityType::Procedure, "p");
    Synonym assignSyn(EntityType::Assign, "a");
    std::string validString = "procName"; // Example of a valid non-empty string for procedure names
    std::string wildcard = "_";
    std::string characterString = "\"charString\"";
    std::string exactMatch = "\"x*y\"";
    std::string partialMatch = "_\"x*y\"_";

    SECTION("ModifiesPredicate and UsesPredicate Validation") {
        // ModifiesPredicate: LHS can be stmt, proc (synonym or string); RHS must be a variable (synonym or string)
        REQUIRE_NOTHROW(ModifiesPredicate(stmtSyn, varSyn));
        REQUIRE_NOTHROW(ModifiesPredicate(procSyn, varSyn));
        REQUIRE_NOTHROW(ModifiesPredicate(characterString, varSyn)); // LHS as procedure name string
        REQUIRE_NOTHROW(ModifiesPredicate(wildcard, varSyn)); // LHS as wildcard

        // UsesPredicate: Similar to Modifies, but for "uses" relationships
        REQUIRE_NOTHROW(UsesPredicate(stmtSyn, varSyn));
        REQUIRE_NOTHROW(UsesPredicate(procSyn, varSyn));
        REQUIRE_NOTHROW(UsesPredicate(characterString, varSyn)); // LHS as procedure name string
        REQUIRE_NOTHROW(UsesPredicate(wildcard, varSyn)); // LHS as wildcard
    }

    SECTION("FollowsPredicate and FollowsTPredicate Validation") {
        // Both predicates expect stmt references (synonym or int)
        REQUIRE_NOTHROW(FollowsPredicate(stmtSyn, stmtSyn2));
        REQUIRE_THROWS(FollowsPredicate(procSyn, stmtSyn2)); // Invalid LHS type
        REQUIRE_NOTHROW(FollowsTPredicate(stmtSyn, stmtSyn2));
        REQUIRE_THROWS(FollowsTPredicate(procSyn, stmtSyn2)); // Invalid LHS type for FollowsT
    }

    SECTION("ParentPredicate and ParentTPredicate Validation") {
        // Both predicates expect stmt references (synonym or int) for parent-child relationships
        REQUIRE_NOTHROW(ParentPredicate(stmtSyn, stmtSyn2));
        REQUIRE_THROWS(ParentPredicate(procSyn, stmtSyn2)); // Procedure cannot be a parent
        REQUIRE_NOTHROW(ParentTPredicate(stmtSyn, stmtSyn2));
        REQUIRE_THROWS(ParentTPredicate(procSyn, stmtSyn2)); // Invalid LHS type for ParentT
    }

    SECTION("AssignPatternPredicate Validation") {
        REQUIRE_NOTHROW(AssignPatternPredicate(assignSyn, varSyn, wildcard));
        REQUIRE_NOTHROW(AssignPatternPredicate(assignSyn, wildcard, exactMatch));
        REQUIRE_NOTHROW(AssignPatternPredicate(assignSyn, characterString, partialMatch));
        REQUIRE_THROWS(AssignPatternPredicate(procSyn, varSyn, wildcard)); // Pattern predicate must be assign
        REQUIRE_THROWS(AssignPatternPredicate(assignSyn, procSyn, wildcard)); // LHS cannot be procedure synonym
        REQUIRE_THROWS(AssignPatternPredicate(assignSyn, validString, wildcard)); // LHS character string must have ""
        REQUIRE_THROWS(AssignPatternPredicate(assignSyn, varSyn, validString)); // Invalid RHS expression for matching 
    }

    SECTION("Wildcard and Non-empty String Checks") {
        // Ensuring wildcard and non-empty strings are valid for LHS where applicable
        REQUIRE_NOTHROW(ParentTPredicate(wildcard, stmtSyn2));
        REQUIRE_NOTHROW(FollowsTPredicate(wildcard, stmtSyn2));
        REQUIRE_NOTHROW(ModifiesPredicate(wildcard, varSyn));
        REQUIRE_NOTHROW(UsesPredicate(characterString, varSyn)); // Procedure name as LHS
        REQUIRE_THROWS(ModifiesPredicate("", varSyn)); // Empty string for LHS should throw
        REQUIRE_THROWS(UsesPredicate("", varSyn)); // Empty string for LHS should throw
    }
}


// ai-gen end