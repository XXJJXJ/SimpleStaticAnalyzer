#include <catch.hpp>
#include "qps/QueryValidator.h"
#include "common/spa_exception/SyntaxErrorException.h"

QueryValidator validator;

TEST_CASE("Test QueryValidator::validateDeclaration") {
    SECTION("Valid declarations") {
        std::vector<std::string> tokens1 = {"variable", "a", ",", "b", ",", "c", ";"};
        std::vector<std::string> tokens2 = {"assign", "a", ";"};

        std::vector<std::string> expectedResults1 = {"variable", "a", "b", "c"};
        std::vector<std::string> expectedResults2 = {"assign", "a"};

        std::vector<std::string> results1 = QueryValidator::validateDeclaration(tokens1);
        std::vector<std::string> results2 = QueryValidator::validateDeclaration(tokens2);

        REQUIRE(results1 == expectedResults1);
        REQUIRE(results2 == expectedResults2);
    }

    SECTION("Invalid declarations") {
        std::vector<std::string> tokens1 = {"invalidKeyword", "a", ",", "b", ",", "c", ";"}; // Invalid keyword
        std::vector<std::string> tokens2 = {"variable", "a", "b", ",", "c", ";"}; // Missing comma
        std::vector<std::string> tokens3 = {"variable", "a", ",", "b", ",", "c", ",", ";"}; // Extra comma
        std::vector<std::string> tokens4 = {"variable", "123invalidName", ",", "b", ",", "c", ";"}; // Invalid synonym name

        REQUIRE_THROWS_AS(QueryValidator::validateDeclaration(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateDeclaration(tokens2), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateDeclaration(tokens3), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateDeclaration(tokens4), SyntaxErrorException);
    }
}

TEST_CASE("Test QueryValidator::validateSelection") {
    SECTION("Valid selections") {
        std::vector<std::string> tokens1 = {"Select", "a"};
        std::vector<std::string> tokens2 = {"Select", "<", "a", ",", "b", ",", "c",">"};
        std::vector<std::string> tokens3 = {"Select", "BOOLEAN"};

        std::vector<std::string> expectedResults1 = {"a"};
        std::vector<std::string> expectedResults2 = {"a", "b", "c"};
        std::vector<std::string> expectedResults3 = {"BOOLEAN"};

        std::vector<std::string> results1 = QueryValidator::validateSelection(tokens1);
        std::vector<std::string> results2 = QueryValidator::validateSelection(tokens2);
        std::vector<std::string> results3 = QueryValidator::validateSelection(tokens3);

        REQUIRE(results1 == expectedResults1);
        REQUIRE(results2 == expectedResults2);
        REQUIRE(results3 == expectedResults3);
    }

    SECTION("Invalid selections") {
        std::vector<std::string> tokens1 = {"Select", "123invalidName"}; // Invalid name
        std::vector<std::string> tokens2 = {"Select", "<", "a", ",", "b", ",", "c", ",", ">"}; // Extra comma
        std::vector<std::string> tokens3 = {"Select", "<", "a", "b", ",", "c",">"}; // No comma
        std::vector<std::string> tokens4 = {"Select", "a", ",", "b", ",", "c", ">"}; // No opening bracket

        REQUIRE_THROWS_AS(QueryValidator::validateSelection(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateSelection(tokens2), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateSelection(tokens3), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateSelection(tokens4), SyntaxErrorException);
    }
}

TEST_CASE("Test QueryValidator::validatePredicate") {
    // Testing switch case, actual correctness of results tested in the various specific validate___Predicate tests below
    SECTION("Valid predicates") {
        std::vector<std::string> tokens1 = {"such", "that", "Follows", "(", "a", ",", "b", ")"};
        std::vector<std::string> tokens2 = {"such", "that", "Follows*", "(", "a", ",", "b", ")"};
        std::vector<std::string> tokens3 = {"such", "that", "Modifies", "(", "a", ",", "b", ")"};
        std::vector<std::string> tokens4 = {"such", "that", "Parent", "(", "a", ",", "b", ")"};
        std::vector<std::string> tokens5 = {"such", "that", "Parent*", "(", "a", ",", "b", ")"};
        std::vector<std::string> tokens6 = {"such", "that", "Uses", "(", "a", ",", "b", ")"};
        std::vector<std::string> tokens7 = {"such", "that", "Calls", "(", "a", ",", "b", ")"};
        std::vector<std::string> tokens8 = {"such", "that", "Calls*", "(", "a", ",", "b", ")"};
        std::vector<std::string> tokens9 = {"pattern", "a", "(", "_", ",", "_", ")"};
        std::vector<std::string> tokens10 = {"such", "that", "Next", "(", "a", ",", "b", ")"};
        std::vector<std::string> tokens11 = {"such", "that", "Next*", "(", "a", ",", "b", ")"};

        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens1));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens2));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens3));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens4));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens5));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens6));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens7));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens8));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens9));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens10));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens11));
    }

    SECTION("Invalid predicates") {
        std::vector<std::string> tokens1 = {"such", "that", "pattern", "a", "(", "_", ",", "_", ")"}; // such that pattern
        std::vector<std::string> tokens2 = {"invalidKeyword", "(", "a", ",", "b", ",", "c", ")"}; // Invalid keyword

        REQUIRE_THROWS_AS(QueryValidator::validatePredicate(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validatePredicate(tokens2), SyntaxErrorException);
    }
}

TEST_CASE("Test QueryValidator::validateStatementStatementPredicate") {
    SECTION("Valid StatementStatementPredicates") {
        std::vector<std::string> tokens1 = {"Follows", "(", "a", ",", "b", ")"}; // Both synonyms
        std::vector<std::string> tokens2 = {"Follows*", "(", "a", ",", "_", ")"}; // Synonym + wildcard
        std::vector<std::string> tokens3 = {"Parent", "(", "a", ",", "3", ")"}; // Synonym + statement number
        std::vector<std::string> tokens4 = {"Parent*", "(", "_", ",", "5", ")"}; // Wildcard + statement number
        std::vector<std::string> tokens5 = {"Next", "(", "a", ",", "b", ")"}; // Both synonyms
        std::vector<std::string> tokens6 = {"Next*", "(", "a", ",", "_", ")"}; // Synonym + wildcard

        std::vector<std::string> expectedResults1 = {"Follows", "a", "b"};
        std::vector<std::string> expectedResults2 = {"Follows*", "a", "_"};
        std::vector<std::string> expectedResults3 = {"Parent", "a", "3"};
        std::vector<std::string> expectedResults4 = {"Parent*", "_", "5"};
        std::vector<std::string> expectedResults5 = {"Next", "a", "b"};
        std::vector<std::string> expectedResults6 = {"Next*", "a", "_"};

        std::vector<std::string> results1 = QueryValidator::validateStatementStatementPredicate(tokens1);
        std::vector<std::string> results2 = QueryValidator::validateStatementStatementPredicate(tokens2);
        std::vector<std::string> results3 = QueryValidator::validateStatementStatementPredicate(tokens3);
        std::vector<std::string> results4 = QueryValidator::validateStatementStatementPredicate(tokens4);
        std::vector<std::string> results5 = QueryValidator::validateStatementStatementPredicate(tokens5);
        std::vector<std::string> results6 = QueryValidator::validateStatementStatementPredicate(tokens6);

        REQUIRE(results1 == expectedResults1);
        REQUIRE(results2 == expectedResults2);
        REQUIRE(results3 == expectedResults3);
        REQUIRE(results4 == expectedResults4);
        REQUIRE(results5 == expectedResults5);
        REQUIRE(results6 == expectedResults6);
    }

    SECTION("Invalid StatementStatementPredicates") {
        std::vector<std::string> tokens1 = {"Follows", "(", "a", ",", "b", ",", "c", ")"}; // Invalid number of arguments
        std::vector<std::string> tokens2 = {"Follows*", "(", "123invalidName", ",", "b", ")"}; // Invalid synonym
        std::vector<std::string> tokens3 = {"Parent", "(", "1", ",", "\"b\"", ")"}; // Invalid string

        REQUIRE_THROWS_AS(QueryValidator::validateStatementStatementPredicate(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateStatementStatementPredicate(tokens2), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateStatementStatementPredicate(tokens3), SyntaxErrorException);
    }
}

TEST_CASE("Test QueryValidator::validateStmtEntEntityPredicate") {
    SECTION("Valid StatementEntityPredicates") {
        std::vector<std::string> tokens1 = {"Uses", "(", "a", ",", "b", ")"}; // Both synonyms
        std::vector<std::string> tokens2 = {"Uses", "(", "1", ",", "_", ")"}; // LHS statement number, RHS wildcard
        std::vector<std::string> tokens3 = {"Modifies", "(", "\"validProcName\"", ",", "\"validVarName\"", ")"}; // LHS valid procedure name, RHS valid variable name
        std::vector<std::string> tokens4 = {"Modifies", "(", "_", ",", "b", ")"}; // LHS wildcard, syntactically valid so will not get caught here, but will be caught later on as a semantic error

        std::vector<std::string> expectedResults1 = {"Uses", "a", "b"};
        std::vector<std::string> expectedResults2 = {"Uses", "1", "_"};
        std::vector<std::string> expectedResults3 = {"Modifies", "\"validProcName\"", "\"validVarName\""};
        std::vector<std::string> expectedResults4 = {"Modifies", "_", "b"};

        std::vector<std::string> results1 = QueryValidator::validateStmtEntEntityPredicate(tokens1);
        std::vector<std::string> results2 = QueryValidator::validateStmtEntEntityPredicate(tokens2);
        std::vector<std::string> results3 = QueryValidator::validateStmtEntEntityPredicate(tokens3);
        std::vector<std::string> results4 = QueryValidator::validateStmtEntEntityPredicate(tokens4);

        REQUIRE(results1 == expectedResults1);
        REQUIRE(results2 == expectedResults2);
        REQUIRE(results3 == expectedResults3);
        REQUIRE(results4 == expectedResults4);
    }

    SECTION("Invalid StatementEntityPredicates") {
        std::vector<std::string> tokens1 = {"Uses", "(", "123invalidName", ",", "b", ")"}; // LHS invalid name
        std::vector<std::string> tokens2 = {"Uses", "(", "\"123invalidString\"", ",", "b", ")"}; // LHS invalid string
        std::vector<std::string> tokens3 = {"Uses", "(", "a", ",", "1", ")"}; // RHS number
        std::vector<std::string> tokens4 = {"Modifies", "(", "a", ",", "123invalidName", ")"}; // RHS invalid name
        std::vector<std::string> tokens5 = {"Modifies", "(", "a", ",", "\"123invalidString\"", ")"}; // RHS invalid string

        REQUIRE_THROWS_AS(QueryValidator::validateStmtEntEntityPredicate(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateStmtEntEntityPredicate(tokens2), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateStmtEntEntityPredicate(tokens3), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateStmtEntEntityPredicate(tokens4), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateStmtEntEntityPredicate(tokens5), SyntaxErrorException);
    }
}

TEST_CASE("Test QueryValidator::validateEntityEntityPredicate") {
    SECTION("Valid EntityEntityPredicates") {
        std::vector<std::string> tokens1 = { "Calls", "(", "a", ",", "b", ")" }; // Both synonyms
        std::vector<std::string> tokens2 = { "Calls", "(", "_", ",", "_", ")" }; // Both wildcards
        std::vector<std::string> tokens3 = { "CallsT", "(", "\"validProcName\"", ",", "\"validProcName\"", ")" }; // Both valid procedure names

        std::vector<std::string> expectedResults1 = { "Calls", "a", "b"};
        std::vector<std::string> expectedResults2 = { "Calls", "_", "_" };
        std::vector<std::string> expectedResults3 = { "CallsT", "\"validProcName\"", "\"validProcName\"" };

        std::vector<std::string> results1 = QueryValidator::validateEntityEntityPredicate(tokens1);
        std::vector<std::string> results2 = QueryValidator::validateEntityEntityPredicate(tokens2);
        std::vector<std::string> results3 = QueryValidator::validateEntityEntityPredicate(tokens3);

        REQUIRE(results1 == expectedResults1);
        REQUIRE(results2 == expectedResults2);
        REQUIRE(results3 == expectedResults3);
    }

    SECTION("Invalid EntityEntityPredicate") {
        std::vector<std::string> tokens1 = { "Calls", "(", "1", ",", "b", ")" }; // LHS number
        std::vector<std::string> tokens2 = { "Calls", "(", "_", ",", "123invalidSynonym", ")" }; // RHS invalid synonym
        std::vector<std::string> tokens3 = { "CallsT", "(", "\"123InvalidProcName\"", ",", "\"validProcName\"", ")" }; // LHS invalid procedure name

        REQUIRE_THROWS_AS(QueryValidator::validateEntityEntityPredicate(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateEntityEntityPredicate(tokens2), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateEntityEntityPredicate(tokens3), SyntaxErrorException);
    }
}

TEST_CASE("Test QueryValidator::validatePatternPredicate") {
    SECTION("Valid PatternPredicates") {
        std::vector<std::string> tokens1 = {"pattern", "a", "(", "_", ",", "_", ")"}; // Both wildcard
        std::vector<std::string> tokens2 = {"pattern", "a", "(", "\"validString\"", ",", "_\"x+y\"_", ")"}; // LHS valid string, RHS partial match
        std::vector<std::string> tokens3 = {"pattern", "a", "(", "validName", ",", "\"x+y\"", ")"}; // LHS valid synonym, RHS complete match
        std::vector<std::string> tokens4 = {"pattern", "a", "(", "validName", ",", "_", ",", "_", ")"}; // Valid If pattern

        std::vector<std::string> expectedResults1 = {"pattern", "a", "_", "_"};
        std::vector<std::string> expectedResults2 = {"pattern", "a", "\"validString\"", "_\"x+y\"_"};
        std::vector<std::string> expectedResults3 = {"pattern", "a", "validName", "\"x+y\""};
        std::vector<std::string> expectedResults4 = {"pattern", "a", "validName", "_", "_"};

        std::vector<std::string> results1 = QueryValidator::validatePatternPredicate(tokens1);
        std::vector<std::string> results2 = QueryValidator::validatePatternPredicate(tokens2);
        std::vector<std::string> results3 = QueryValidator::validatePatternPredicate(tokens3);
        std::vector<std::string> results4 = QueryValidator::validatePatternPredicate(tokens4);

        REQUIRE(results1 == expectedResults1);
        REQUIRE(results2 == expectedResults2);
        REQUIRE(results3 == expectedResults3);
        REQUIRE(results4 == expectedResults4);
    }

    SECTION("Invalid PatternPredicates") {
        std::vector<std::string> tokens1 = {"pattern", "123invalidName", "(", "_", ",", "_", ")"}; // Invalid synonym
        std::vector<std::string> tokens2 = {"pattern", "a", "(", "123invalidName", ",", "_", ")"}; // LHS invalid name
        std::vector<std::string> tokens3 = {"pattern", "a", "(", "\"123invalidString\"", ",", "_", ")"}; // LHS invalid string
        std::vector<std::string> tokens4 = {"pattern", "a", "(", "1", ",", "_", ")"}; // LHS number
        std::vector<std::string> tokens5 = { "pattern", "a", "(", "_", ",", "validName", ",", "\"validString\"", ")" }; // Invalid If pattern

        REQUIRE_THROWS_AS(QueryValidator::validatePatternPredicate(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validatePatternPredicate(tokens2), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validatePatternPredicate(tokens3), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validatePatternPredicate(tokens4), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validatePatternPredicate(tokens5), SyntaxErrorException);
    }
}

// Actual validity of each component already tested above, only testing that all 3 components work together correctly here 
TEST_CASE("Test QueryValidator::validate") {
    SECTION("Valid query") {
        std::vector<std::vector<std::vector<std::string>>> tokens1 = {{{"variable", "a", ",", "b", ",", "c", ";"}, {"assign", "a", ";"}},
                                                                      {{"Select", "a"}},
                                                                      {{"such", "that", "Follows", "(", "a", ",", "b", ")"}, {"pattern", "a", "(", "_", ",", "_", ")"}}};
        std::vector<std::vector<std::vector<std::string>>> tokens2 = {{},
                                                                      {{"Select", "<", "a", ",", "b", ",", "c",">"}},
                                                                      {{"such", "that", "Follows", "(", "a", ",", "b", ")"}, {"pattern", "a", "(", "_", ",", "_", ")"}}}; // No declaration, syntactically valid but semantically invalid

        REQUIRE_NOTHROW(QueryValidator::validate(tokens1));
        REQUIRE_NOTHROW(QueryValidator::validate(tokens2));
    }

    SECTION("Invalid query") {
        std::vector<std::vector<std::vector<std::string>>> tokens1 = {{{"invalidKeyword", "a", ",", "b", ",", "c", ";"}, {"assign", "a", ";"}},
                                                                      {{"Select", "a"}},
                                                                      {{"such", "that", "Follows", "(", "a", ",", "b", ")"}, {"pattern", "a", "(", "_", ",", "_", ")"}}}; // Invalid declaration
        std::vector<std::vector<std::vector<std::string>>> tokens2 = {{{"variable", "a", ",", "b", ",", "c", ";"}, {"assign", "a", ";"}},
                                                                      {{"Select", "123invalidName"}},
                                                                      {{"such", "that", "Follows", "(", "a", ",", "b", ")"}, {"pattern", "a", "(", "_", ",", "_", ")"}}}; // Invalid selection
        std::vector<std::vector<std::vector<std::string>>> tokens3 = {{{"variable", "a", ",", "b", ",", "c", ";"}, {"assign", "a", ";"}},
                                                                      {{"Select", "<", "a", ",", "b", ",", "c",">"}},
                                                                      {{"such", "that", "Follows", "(", "a", ",", "b", ")"}, {"pattern", "123invalidName", "(", "_", ",", "_", ")"}}}; // Invalid predicate
        std::vector<std::vector<std::vector<std::string>>> tokens4 = {{{"variable", "a", ",", "b", ",", "c", ";"}, {"assign", "a", ";"}},
                                                                      {},
                                                                      {{"such", "that", "Follows", "(", "a", ",", "b", ")"}, {"pattern", "a", "(", "_", ",", "_", ")"}}}; // No selection

        REQUIRE_THROWS_AS(QueryValidator::validate(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validate(tokens2), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validate(tokens3), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validate(tokens4), SyntaxErrorException);
    }
}


//ai-gen start(gpt, 2, e)
// prompt: https://chat.openai.com/share/c3dec1ba-84fd-4fdb-ab11-c7f34bf4ef59

TEST_CASE("Test isLetter method", "[isLetter]") {
	REQUIRE(validator.isLetter("a"));
	REQUIRE(validator.isLetter("A"));
	REQUIRE(!validator.isLetter("1"));
	REQUIRE(!validator.isLetter("*"));
	REQUIRE(!validator.isLetter(""));
}

TEST_CASE("Test isDigit method", "[isDigit]") {
	REQUIRE(validator.isDigit("0"));
	REQUIRE(validator.isDigit("5"));
	REQUIRE(validator.isDigit("9"));
	REQUIRE(!validator.isDigit("10"));
	REQUIRE(!validator.isDigit("A"));
	REQUIRE(!validator.isDigit(""));
}

TEST_CASE("Test isNzDigit method", "[isNzDigit]") {
	REQUIRE(validator.isNzDigit("1"));
	REQUIRE(validator.isNzDigit("2"));
	REQUIRE(validator.isNzDigit("9"));
	REQUIRE(!validator.isNzDigit("0"));
	REQUIRE(!validator.isNzDigit("10"));
	REQUIRE(!validator.isNzDigit("A"));
	REQUIRE(!validator.isNzDigit(""));
}

// Definition of integer: 0 | NZDIGIT ( DIGIT )* - no leading zero
TEST_CASE("Test isInteger method", "[isInteger]") {
	REQUIRE(validator.isInteger("0"));
	REQUIRE(validator.isInteger("1"));
	REQUIRE(validator.isInteger("9"));
	REQUIRE(validator.isInteger("10"));
	REQUIRE(validator.isInteger("123"));
	REQUIRE(!validator.isInteger("01"));
	REQUIRE(!validator.isInteger("A"));
    REQUIRE(!validator.isInteger("Long_Invalid_Chars"));
    REQUIRE(!validator.isInteger("12Mix0fCh@rs"));
	REQUIRE(!validator.isInteger(""));
}

// Definition of identifier (IDENT): LETTER ( LETTER | DIGIT )*
TEST_CASE("Test isIdent method", "[isIdent]") {
	REQUIRE(validator.isIdent("variable"));
	REQUIRE(validator.isIdent("Variable1"));
	REQUIRE(!validator.isIdent("123variable"));
	REQUIRE(!validator.isIdent("_variable"));
	REQUIRE(!validator.isIdent("123"));
	REQUIRE(!validator.isIdent(""));
}

// Definition of synonym: IDENT
TEST_CASE("Test isSynonym method", "[isSynonym]") {
	REQUIRE(validator.isSynonym("stmt"));
	REQUIRE(validator.isSynonym("variable"));
	REQUIRE(validator.isSynonym("read"));
	REQUIRE(validator.isSynonym("xyz"));
	REQUIRE(!validator.isSynonym(""));
}

// Definition of stmtRef: synonym | '_' | INTEGER
TEST_CASE("Test isStmtRef method", "[isStmtRef]") {
	REQUIRE(validator.isStmtRef("stmt"));
	REQUIRE(validator.isStmtRef("_"));
	REQUIRE(validator.isStmtRef("10"));
	REQUIRE(validator.isStmtRef("xyz"));
	REQUIRE(!validator.isStmtRef(""));
}

TEST_CASE("Test isEntRef method", "[isEntRef]") {
	REQUIRE(validator.isEntRef("stmt"));
	REQUIRE(validator.isEntRef("_"));
	REQUIRE(validator.isEntRef("\"variable\""));
	REQUIRE(!validator.isEntRef("\"_\""));
	REQUIRE(!validator.isEntRef("\"123\""));
	REQUIRE(validator.isEntRef("xyz"));
	REQUIRE(!validator.isEntRef(""));
}
// ai-gen end

TEST_CASE("Test isExpr", "[isExpr]") {
    REQUIRE(QueryValidator::isExpr("x+y"));
    REQUIRE(QueryValidator::isExpr("a-b"));
    REQUIRE(QueryValidator::isExpr("a+b-c"));
    REQUIRE(QueryValidator::isExpr("a*b+c"));
    REQUIRE(QueryValidator::isExpr("(a+b)*c"));
    REQUIRE(QueryValidator::isExpr("a+b*(c-d)"));
    REQUIRE(QueryValidator::isExpr("a"));
    REQUIRE(QueryValidator::isExpr("(a)"));
    REQUIRE(QueryValidator::isExpr("2"));
    REQUIRE(QueryValidator::isExpr("x+y*v "));
    REQUIRE(QueryValidator::isExpr("a * b + c"));

    REQUIRE_FALSE(QueryValidator::isExpr(""));
    REQUIRE_FALSE(QueryValidator::isExpr("a+b+c+"));
    REQUIRE_FALSE(QueryValidator::isExpr("*a+b"));
}

TEST_CASE("Test isTerm", "[isTerm]") {
    REQUIRE(QueryValidator::isTerm("x*y"));
    REQUIRE(QueryValidator::isTerm("a/b"));
    REQUIRE(QueryValidator::isTerm("a%b"));
    REQUIRE(QueryValidator::isTerm("a*b/c"));
    REQUIRE(QueryValidator::isTerm("(a+b)*c"));
    REQUIRE(QueryValidator::isTerm("a*b*(c-d)"));
    REQUIRE(QueryValidator::isTerm("a"));
    REQUIRE(QueryValidator::isTerm("(a)"));

    REQUIRE_FALSE(QueryValidator::isTerm(""));
    REQUIRE_FALSE(QueryValidator::isTerm("a*b*c*"));
    REQUIRE_FALSE(QueryValidator::isTerm("+a*b"));
}

TEST_CASE("Test isFactor", "[isFactor]") {
    REQUIRE(QueryValidator::isFactor("x"));
    REQUIRE(QueryValidator::isFactor("y"));
    REQUIRE(QueryValidator::isFactor("a"));
    REQUIRE(QueryValidator::isFactor("abc123"));
    REQUIRE(QueryValidator::isFactor("(a+b)"));

    REQUIRE_FALSE(QueryValidator::isFactor(""));
    REQUIRE_FALSE(QueryValidator::isFactor("a+b"));
    REQUIRE_FALSE(QueryValidator::isFactor("(a+b"));
    REQUIRE_FALSE(QueryValidator::isFactor("a+b)"));
}