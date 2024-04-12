#include <catch.hpp>
#include "qps/QueryValidator.h"
#include "common/spa_exception/SyntaxErrorException.h"

TEST_CASE("QueryValidator::splitTokens should correctly split query into lists of tokens, where each list is a part of the query") {
	std::vector<std::string> testQuery = { "variable", "a", ";", 
                                           "Select", "a", 
                                           "such", "that", "Follows", "(", "a", ",", "_", ")", 
                                           "with", "a.stmt#", "=", "8", 
                                           "pattern", "a", "(", "_", ",", "_", ")"};

	std::vector<std::vector<std::vector<std::string>>> result = QueryValidator::splitTokens(testQuery);

	std::vector<std::vector<std::vector<std::string>>> expectedResult = { {{"variable", "a", ";"}}, 
                                                                          {{"Select", "a"}}, 
                                                                          {{"such", "that", "Follows", "(", "a", ",", "_", ")"}, {"with", "a.stmt#", "=", "8"}, {"pattern", "a", "(", "_", ",", "_", ")"}} };

	REQUIRE(result == expectedResult);
}

TEST_CASE("QueryValidator::splitTokens should support synonyms with names that are same as keywords") {
	std::vector<std::string> testQuery = { "variable", "Select", ",", "assign", ";", "assign", "variable", ";", "Select", "Select" };

	std::vector<std::vector<std::vector<std::string>>> result = QueryValidator::splitTokens(testQuery);

	std::vector<std::vector<std::vector<std::string>>> expectedResult = { {{"variable", "Select", ",", "assign", ";"}, {"assign", "variable", ";"}}, {{"Select", "Select"}}, {} };

	REQUIRE(result == expectedResult);
}

TEST_CASE("QueryValidator::splitTokens should throw error if clauses are in the wrong order") {
    std::vector<std::string> testQuery1 = { "variable", "a", ",", "b", ";", "assign", "c", ";", 
                                            "Select", "a", 
                                            "such", "that", "Follows", "(", "a", ",", "_", "_", ")", "pattern", "a", "(", "_", "_", ",", "_", "_", ")" };
    std::vector<std::string> testQuery2 = { "variable", "a", ",", "b", ";", 
                                            "Select", "a", 
                                            "assign", "c", ";", 
                                            "such", "that", "Follows", "(", "a", ",", "_", "_", ")", "pattern", "a", "(", "_", "_", ",", "_", "_", ")" };  // Declaration after Select
    std::vector<std::string> testQuery3 = { "variable", "a", ",", "b", ";", 
                                            "such", "that", "Follows", "(", "a", ",", "_", "_", ")", 
                                            "assign", "c", ";",
                                            "Select", "a", 
                                            "pattern", "a", "(", "_", "_", ",", "_", "_", ")" };  // Clause before Declaration
    std::vector<std::string> testQuery4 = { "variable", "a", ",", "b", ";", "assign", "c", ";", 
                                            "such", "that", "Follows", "(", "a", ",", "_", "_", ")", "pattern", "a", "(", "_", "_", ",", "_", "_", ")", 
                                            "Select", "a" };  // Select after clause

    REQUIRE_NOTHROW(QueryValidator::splitTokens(testQuery1));
    REQUIRE_THROWS(QueryValidator::splitTokens(testQuery2));
    REQUIRE_THROWS(QueryValidator::splitTokens(testQuery3));
    REQUIRE_THROWS(QueryValidator::splitTokens(testQuery4));
}

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
        std::vector<std::string> tokens2 = {"Select", "<", "a", ",", "b", ",", "c", ">"};
        std::vector<std::string> tokens3 = {"Select", "BOOLEAN"};
        std::vector<std::string> tokens4 = {"Select", "a.procName"};
        std::vector<std::string> tokens5 = {"Select", "<", "a", ",", "a.procName", ",", "a.varName", ",", "a.value", ",", "a.stmt#", ">"};


        std::vector<std::string> expectedResults1 = {"a"};
        std::vector<std::string> expectedResults2 = {"a", "b", "c"};
        std::vector<std::string> expectedResults3 = {"BOOLEAN"};
        std::vector<std::string> expectedResults4 = {"a.procName"};
        std::vector<std::string> expectedResults5 = {"a", "a.procName", "a.varName", "a.value", "a.stmt#"};

        std::vector<std::string> results1 = QueryValidator::validateSelection(tokens1);
        std::vector<std::string> results2 = QueryValidator::validateSelection(tokens2);
        std::vector<std::string> results3 = QueryValidator::validateSelection(tokens3);
        std::vector<std::string> results4 = QueryValidator::validateSelection(tokens4);
        std::vector<std::string> results5 = QueryValidator::validateSelection(tokens5);

        REQUIRE(results1 == expectedResults1);
        REQUIRE(results2 == expectedResults2);
        REQUIRE(results3 == expectedResults3);
        REQUIRE(results4 == expectedResults4);
        REQUIRE(results5 == expectedResults5);
    }

    SECTION("Invalid selections") {
        std::vector<std::string> tokens1 = {"Select", "123invalidName"}; // Invalid name
        std::vector<std::string> tokens2 = {"Select", "<", "a", ",", "b", ",", "c", ",", ">"}; // Extra comma
        std::vector<std::string> tokens3 = {"Select", "<", "a", "b", ",", "c",">"}; // No comma
        std::vector<std::string> tokens4 = {"Select", "a", ",", "b", ",", "c", ">"}; // No opening bracket
        std::vector<std::string> tokens5 = {"Select", "a.attribute"}; // Invalid attribute
        std::vector<std::string> tokens6 = {"Select", "123.procName"}; // Invalid name

        REQUIRE_THROWS_AS(QueryValidator::validateSelection(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateSelection(tokens2), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateSelection(tokens3), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateSelection(tokens4), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateSelection(tokens5), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateSelection(tokens6), SyntaxErrorException);
    }
}

TEST_CASE("Test QueryValidator::validatePredicate") {
    // Testing switch case, actual correctness of results tested in the various specific validate___Predicate tests below
    ClauseType noPrevClause = ClauseType::Invalid;
    ClauseType suchThatClause = ClauseType::SuchThat;
    ClauseType patternClause = ClauseType::Pattern;
    ClauseType withClause = ClauseType::With;
    SECTION("Valid predicates") {
        std::vector<std::string> tokens1 = {"such", "that", "Follows", "(", "a", ",", "b", ")"};
        std::vector<std::string> tokens2 = {"pattern", "a", "(", "_", ",", "_", ")"};
        std::vector<std::string> tokens3 = {"and", "Follows", "(", "a", ",", "b", ")"};
        std::vector<std::string> tokens4 = {"and", "a", "(", "_", ",", "_", ")"};
        std::vector<std::string> tokens5 = {"such", "that", "not", "Follows", "(", "a", ",", "b", ")"};
        std::vector<std::string> tokens6 = {"with", "a.stmt#", "=", "8"};
        std::vector<std::string> tokens7 = {"and", "not", "a.procName", "=", "\"procName\""};

        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens1, noPrevClause));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens2, noPrevClause));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens3, suchThatClause));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens4, patternClause));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens5, noPrevClause));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens6, noPrevClause));
        REQUIRE_NOTHROW(QueryValidator::validatePredicate(tokens7, withClause));
    }

    SECTION("Invalid predicates") {
        std::vector<std::string> tokens1 = {"such", "that", "pattern", "a", "(", "_", ",", "_", ")"}; // such that pattern
        std::vector<std::string> tokens2 = {"such", "thatIsWrong", "(", "a", ",", "b", ")"}; // Invalid keyword
        std::vector<std::string> tokens3 = { "and", "Follows", "(", "a", ",", "b", ")" };
        std::vector<std::string> tokens4 = { "and", "a", "(", "_", ",", "_", ")" };
        std::vector<std::string> tokens5 = { "not", "a", "(", "_", ",", "_", ")" };
        std::vector<std::string> tokens6 = {"and", "a.stmt#", "=", "8"};

        REQUIRE_THROWS_AS(QueryValidator::validatePredicate(tokens1, noPrevClause), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validatePredicate(tokens2, noPrevClause), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validatePredicate(tokens3, patternClause), SyntaxErrorException); // Pattern pred and such that pred
        REQUIRE_THROWS_AS(QueryValidator::validatePredicate(tokens4, suchThatClause), SyntaxErrorException); // Such that pred and pattern pred
        REQUIRE_THROWS_AS(QueryValidator::validatePredicate(tokens5, noPrevClause), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validatePredicate(tokens6, patternClause), SyntaxErrorException); // Pattern pred and with pred
    }
}

TEST_CASE("Test QueryValidator::validateSuchThatPredicate") {
    SECTION("Valid predicates") {
        std::vector<std::string> tokens1 = { "Follows", "(", "a", ",", "b", ")" };
        std::vector<std::string> tokens2 = { "Follows*", "(", "a", ",", "b", ")" };
        std::vector<std::string> tokens3 = { "Modifies", "(", "a", ",", "b", ")" };
        std::vector<std::string> tokens4 = { "Parent", "(", "a", ",", "b", ")" };
        std::vector<std::string> tokens5 = { "Parent*", "(", "a", ",", "b", ")" };
        std::vector<std::string> tokens6 = { "Uses", "(", "a", ",", "b", ")" };
        std::vector<std::string> tokens7 = { "Calls", "(", "a", ",", "b", ")" };
        std::vector<std::string> tokens8 = { "Calls*", "(", "a", ",", "b", ")" };
        std::vector<std::string> tokens9 = { "not", "Follows", "(", "a", ",", "b", ")"};

        REQUIRE_NOTHROW(QueryValidator::validateSuchThatPredicate(tokens1));
        REQUIRE_NOTHROW(QueryValidator::validateSuchThatPredicate(tokens2));
        REQUIRE_NOTHROW(QueryValidator::validateSuchThatPredicate(tokens3));
        REQUIRE_NOTHROW(QueryValidator::validateSuchThatPredicate(tokens4));
        REQUIRE_NOTHROW(QueryValidator::validateSuchThatPredicate(tokens5));
        REQUIRE_NOTHROW(QueryValidator::validateSuchThatPredicate(tokens6));
        REQUIRE_NOTHROW(QueryValidator::validateSuchThatPredicate(tokens7));
        REQUIRE_NOTHROW(QueryValidator::validateSuchThatPredicate(tokens8));
        REQUIRE_NOTHROW(QueryValidator::validateSuchThatPredicate(tokens9));
    }

    SECTION("Invalid predicates") {
        std::vector<std::string> tokens1 = { "pattern", "a", "(", "_", ",", "_", ")" }; // such that pattern
        std::vector<std::string> tokens2 = { "invalidKeyword", "(", "a", ",", "b", ")" }; // Invalid keyword

        REQUIRE_THROWS_AS(QueryValidator::validateSuchThatPredicate(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateSuchThatPredicate(tokens2), SyntaxErrorException);
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
        std::vector<std::string> tokens7 = {"Affects", "(", "a", ",", "_", ")"}; // Synonym + wildcard

        std::vector<std::string> expectedResults1 = {"Follows", "a", "b"};
        std::vector<std::string> expectedResults2 = {"Follows*", "a", "_"};
        std::vector<std::string> expectedResults3 = {"Parent", "a", "3"};
        std::vector<std::string> expectedResults4 = {"Parent*", "_", "5"};
        std::vector<std::string> expectedResults5 = {"Next", "a", "b"};
        std::vector<std::string> expectedResults6 = {"Next*", "a", "_"};
        std::vector<std::string> expectedResults7 = {"Affects", "a", "_"};

        std::vector<std::string> results1 = QueryValidator::validateStatementStatementPredicate(tokens1);
        std::vector<std::string> results2 = QueryValidator::validateStatementStatementPredicate(tokens2);
        std::vector<std::string> results3 = QueryValidator::validateStatementStatementPredicate(tokens3);
        std::vector<std::string> results4 = QueryValidator::validateStatementStatementPredicate(tokens4);
        std::vector<std::string> results5 = QueryValidator::validateStatementStatementPredicate(tokens5);
        std::vector<std::string> results6 = QueryValidator::validateStatementStatementPredicate(tokens6);
        std::vector<std::string> results7 = QueryValidator::validateStatementStatementPredicate(tokens7);

        REQUIRE(results1 == expectedResults1);
        REQUIRE(results2 == expectedResults2);
        REQUIRE(results3 == expectedResults3);
        REQUIRE(results4 == expectedResults4);
        REQUIRE(results5 == expectedResults5);
        REQUIRE(results6 == expectedResults6);
        REQUIRE(results7 == expectedResults7);
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
        std::vector<std::string> tokens1 = {"a", "(", "_", ",", "_", ")"}; // Both wildcard
        std::vector<std::string> tokens2 = {"a", "(", "\"validString\"", ",", "_\"x+y\"_", ")"}; // LHS valid string, RHS partial match
        std::vector<std::string> tokens3 = {"a", "(", "validName", ",", "\"x+y\"", ")"}; // LHS valid synonym, RHS complete match
        std::vector<std::string> tokens4 = {"a", "(", "validName", ",", "_", ",", "_", ")"}; // Valid If pattern
        std::vector<std::string> tokens5 = {"not", "a", "(", "validName", ",", "_", ",", "_", ")"};  // Valid If pattern

        std::vector<std::string> expectedResults1 = {"pattern", "a", "_", "_"};
        std::vector<std::string> expectedResults2 = {"pattern", "a", "\"validString\"", "_\"x+y\"_"};
        std::vector<std::string> expectedResults3 = {"pattern", "a", "validName", "\"x+y\""};
        std::vector<std::string> expectedResults4 = {"pattern", "a", "validName", "_", "_"};
        std::vector<std::string> expectedResults5 = {"not", "pattern", "a", "validName", "_", "_"};

        std::vector<std::string> results1 = QueryValidator::validatePatternPredicate(tokens1);
        std::vector<std::string> results2 = QueryValidator::validatePatternPredicate(tokens2);
        std::vector<std::string> results3 = QueryValidator::validatePatternPredicate(tokens3);
        std::vector<std::string> results4 = QueryValidator::validatePatternPredicate(tokens4);
        std::vector<std::string> results5 = QueryValidator::validatePatternPredicate(tokens5);

        REQUIRE(results1 == expectedResults1);
        REQUIRE(results2 == expectedResults2);
        REQUIRE(results3 == expectedResults3);
        REQUIRE(results4 == expectedResults4);
        REQUIRE(results5 == expectedResults5);
    }

    SECTION("Invalid PatternPredicates") {
        std::vector<std::string> tokens1 = {"123invalidName", "(", "_", ",", "_", ")"}; // Invalid synonym
        std::vector<std::string> tokens2 = {"a", "(", "123invalidName", ",", "_", ")"}; // LHS invalid name
        std::vector<std::string> tokens3 = {"a", "(", "\"123invalidString\"", ",", "_", ")"}; // LHS invalid string
        std::vector<std::string> tokens4 = {"a", "(", "1", ",", "_", ")"}; // LHS number
        std::vector<std::string> tokens5 = {"a", "(", "_", ",", "validName", ",", "\"validString\"", ")"}; // Invalid If pattern

        REQUIRE_THROWS_AS(QueryValidator::validatePatternPredicate(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validatePatternPredicate(tokens2), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validatePatternPredicate(tokens3), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validatePatternPredicate(tokens4), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validatePatternPredicate(tokens5), SyntaxErrorException);
    }
}

TEST_CASE("Test QueryValidator::isValidPredicateArgsNum") {
    SECTION("Valid number of arguments") {
        std::vector<std::string> tokens1 = { "Follows", "(", "a", ",", "b", ")" };
        std::vector<std::string> tokens2 = { "a", "(", "a", ",", "_", ",", "_", ")" };

        REQUIRE(QueryValidator::isValidPredicateArgsNum(tokens1, 2));
        REQUIRE(QueryValidator::isValidPredicateArgsNum(tokens2, 3));
    }

    SECTION("Invalid number of arguments") {
        std::vector<std::string> tokens1 = { "Follows", "(", "a", ",", "b", ")" };
        std::vector<std::string> tokens2 = { "a", "(", "a", ",", "_", ",", "_", ")" };

        REQUIRE(!QueryValidator::isValidPredicateArgsNum(tokens1, 3));
        REQUIRE(!QueryValidator::isValidPredicateArgsNum(tokens2, 2));
    }

    SECTION("Wrong syntax") {
        std::vector<std::string> tokens1 = { "Follows", "(", "a", "notAComma", "b", ")" };
        std::vector<std::string> tokens2 = { "a", "notABracket", "a", ",", "_", ",", "_", ")" };

        REQUIRE(!QueryValidator::isValidPredicateArgsNum(tokens1, 2));
        REQUIRE(!QueryValidator::isValidPredicateArgsNum(tokens2, 3));
    }
}

TEST_CASE("Test QueryValidator::getPredicateArgs") {
    std::vector<std::string> tokens1 = { "Follows", "(", "a", ",", "b", ")" };
    std::vector<std::string> tokens2 = { "a", "(", "a", ",", "_", ",", "_", ")" };

    std::vector<std::string> expectedResults1 = { "Follows", "a", "b" };
    std::vector<std::string> expectedResults2 = { "a", "a", "_", "_" };

    std::vector<std::string> results1 = QueryValidator::getPredicateArgs(tokens1, 2);
    std::vector<std::string> results2 = QueryValidator::getPredicateArgs(tokens2, 3);

    REQUIRE(results1 == expectedResults1);
    REQUIRE(results2 == expectedResults2);
}

TEST_CASE("Test QueryValidator::validateWithPredicate") {
    SECTION("Valid WithPredicates") {
        std::vector<std::string> tokens1 = {"a.stmt#", "=", "8"};
        std::vector<std::string> tokens2 = {"not", "a.stmt#", "=", "8"};

        std::vector<std::string> expectedResults1 = {"with", "a.stmt#", "8"};
        std::vector<std::string> expectedResults2 = {"not", "with", "a.stmt#", "8"};

        std::vector<std::string> results1 = QueryValidator::validateWithPredicate(tokens1);
        std::vector<std::string> results2 = QueryValidator::validateWithPredicate(tokens2);

        REQUIRE(results1 == expectedResults1);
        REQUIRE(results2 == expectedResults2);
    }

    SECTION("Invalid WithPredicates") {
        std::vector<std::string> tokens1 = {"with", "a.stmt#", "!", "8"}; // no "="
        std::vector<std::string> tokens2 = {"with", "extraToken", "a.stmt#", "=", "8"}; // extra token
        std::vector<std::string> tokens3 = {"with", "a.invalidAttr", "=", "8"}; // lhs invalid
        std::vector<std::string> tokens4 = {"with", "a.stmt#", "=", "invalid123"}; //rhs invalid

        REQUIRE_THROWS_AS(QueryValidator::validateWithPredicate(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateWithPredicate(tokens2), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateWithPredicate(tokens3), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validateWithPredicate(tokens4), SyntaxErrorException);
    }
}

// Actual validity of each component already tested above, only testing that all 3 components work together correctly here 
TEST_CASE("Test QueryValidator::validate") {
    SECTION("Valid query") {
        std::vector<std::string> tokens1 = {"variable", "a", ",", "b", ",", "c", ";", "assign", "a", ";",
                                            "Select", "a",
                                            "such", "that", "Follows", "(", "a", ",", "b", ")", "pattern", "a", "(", "_", ",", "_", ")", "with", "a.stmt#", "=", "8"};
        std::vector<std::string> tokens2 = {"Select", "<", "a", ",", "b", ",", "c",">",
                                            "such", "that", "Follows", "(", "a", ",", "b", ")", "pattern", "a", "(", "_", ",", "_", ")"}; // No declaration, syntactically valid but semantically invalid
        std::vector<std::string> tokens3 = {"variable", "a", ",", "b", ",", "c", ";", "assign", "a", ";",
                                            "Select", "a",
                                            "such", "that", "Follows", "(", "a", ",", "b", ")", "and", "Modifies", "(", "a", ",", "b", ")", "and", "Uses", "(", "a", ",", "b", ")",
                                            "pattern", "a", "(", "_", ",", "_", ")", "and", "b", "(", "validName", ",", "_", ")", "and", "b", "(", "validName", ",", "_", ",", "_", ")",
                                            "with", "a.stmt#", "=", "8", "and", "b.varName", "=", "\"validVarName\""};
        std::vector<std::string> tokens4 = {"variable", "a", ",", "b", ",", "c", ";", "assign", "a", ";",
                                            "Select", "a",
                                            "such", "that", "Follows", "(", "a", ",", "b", ")", "and", "Modifies", "(", "a", ",", "b", ")", "and", "Uses", "(", "a", ",", "b", ")",
                                            "pattern", "a", "(", "_", ",", "_", ")", "and", "Modifies", "(", "a", ",", "_", ")", "and", "b", "(", "validName", ",", "_", ",", "_", ")"}; // Pattern and such that, syntactically valid but semantically invalid
        
        REQUIRE_NOTHROW(QueryValidator::validate(tokens1));
        REQUIRE_NOTHROW(QueryValidator::validate(tokens2));
        REQUIRE_NOTHROW(QueryValidator::validate(tokens3));
        REQUIRE_NOTHROW(QueryValidator::validate(tokens4));
    }

    SECTION("Invalid query") {
        std::vector<std::string> tokens1 = {"invalidKeyword", "a", ",", "b", ",", "c", ";", "assign", "a", ";",
                                            "Select", "a",
                                            "such", "that", "Follows", "(", "a", ",", "b", ")", "pattern", "a", "(", "_", ",", "_", ")"}; // Invalid declaration
        std::vector<std::string> tokens2 = {"variable", "a", ",", "b", ",", "c", ";", "assign", "a", ";",
                                            "Select", "123invalidName",
                                            "such", "that", "Follows", "(", "a", ",", "b", ")", "pattern", "a", "(", "_", ",", "_", ")"}; // Invalid selection
        std::vector<std::string> tokens3 = {"variable", "a", ",", "b", ",", "c", ";", "assign", "a", ";",
                                            "Select", "<", "a", ",", "b", ",", "c",">",
                                            "such", "that", "Follows", "(", "a", ",", "b", ")", "pattern", "123invalidName", "(", "_", ",", "_", ")"}; // Invalid predicate
        std::vector<std::string> tokens4 = {"variable", "a", ",", "b", ",", "c", ";", "assign", "a", ";",
                                            "such", "that", "Follows", "(", "a", ",", "b", ")", "pattern", "a", "(", "_", ",", "_", ")"}; // No selection
        std::vector<std::string> tokens5 = {"variable", "a", ",", "b", ",", "c", ";", "assign", "a", ";",
                                            "Select", "a",
                                            "such", "that", "Follows", "(", "a", ",", "b", ")", "and", "a", "(", "_", ",", "_", ")", "and", "Uses", "(", "a", ",", "b", ")",
                                            "pattern", "a", "(", "_", ",", "_", ")", "and", "b", "(", "validName", ",", "_", ")", "and", "b", "(", "validName", ",", "_", ",", "_", ")"}; // Such that and pattern
        std::vector<std::string> tokens6 = {"variable", "a", ",", "b", ",", "c", ";", "assign", "a", ";",
                                            "Select", "a",
                                            "and", "Follows", "(", "a", ",", "b", ")", "and", "Modifies", "(", "a", ",", "b", ")", "and", "Uses", "(", "a", ",", "b", ")",
                                            "pattern", "a", "(", "_", ",", "_", ")", "and", "b", "(", "validName", ",", "_", ")", "and", "b", "(", "validName", ",", "_", ",", "_", ")"}; // Starts with and clause

        REQUIRE_THROWS_AS(QueryValidator::validate(tokens1), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validate(tokens2), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validate(tokens3), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validate(tokens4), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validate(tokens5), SyntaxErrorException);
        REQUIRE_THROWS_AS(QueryValidator::validate(tokens6), SyntaxErrorException);
    }
}