#include "catch.hpp"
#include "qps/QueryTokenizer.h"
#include <iostream>

TEST_CASE("QueryTokenizer::tokenize should remove trailing whitespaces") {
	std::string testQuery1 = "variable a      ;";
	std::string testQuery2 = "assign     a   ;   Select    a";
	std::string testQuery3 = "procedure   p,   p1; Select     p such      that      Calls(   p,    p1   )    ";

	std::vector<std::string> result1 = QueryTokenizer::tokenize(testQuery1);
	std::vector<std::string> result2 = QueryTokenizer::tokenize(testQuery2);
	std::vector<std::string> result3 = QueryTokenizer::tokenize(testQuery3);

	std::vector<std::string> expectedResult1 = { "variable", "a", ";" };
	std::vector<std::string> expectedResult2 = { "assign", "a", ";", "Select", "a" };
	std::vector<std::string> expectedResult3 = {"procedure", "p", ",", "p1", ";", "Select", "p", "such", "that", "Calls", "(", "p", ",", "p1", ")" };

	REQUIRE(result1 == expectedResult1);
	REQUIRE(result2 == expectedResult2);
	REQUIRE(result3 == expectedResult3);

}

TEST_CASE("QueryTokenizer::tokenize should recognise each punctuation as a separate token") {
	std::string testQuery1 = "variable a,b,c;";
	std::string testQuery2 = "variable a, b, c;assign d,c;";

	std::vector<std::string> result1 = QueryTokenizer::tokenize(testQuery1);
	std::vector<std::string> result2 = QueryTokenizer::tokenize(testQuery2);

	std::vector<std::string> expectedResult1 = { "variable", "a", ",", "b", ",", "c", ";" };
	std::vector<std::string> expectedResult2 = { "variable", "a", ",", "b", ",", "c", ";", "assign", "d", ",", "c", ";" };

	REQUIRE(result1 == expectedResult1);
	REQUIRE(result2 == expectedResult2);
}

TEST_CASE("QueryTokenizer::tokenize should correctly tokenize patterns") {
	std::string testQuery1 = "assign a; Select a pattern a(_, _)"; // both wildcards
	std::string testQuery2 = "assign a; Select a pattern a(_, _\"(a+b)\"_)"; // partial match
	std::string testQuery3 = "assign a; Select a pattern a(_, \"(a+b)\")"; // complete match
	std::string testQuery4 = "assign a; Select a pattern a(_, \"( a+  b)\")"; // complete match with empty spaces

	std::vector<std::string> result1 = QueryTokenizer::tokenize(testQuery1);
	std::vector<std::string> result2 = QueryTokenizer::tokenize(testQuery2);
	std::vector<std::string> result3 = QueryTokenizer::tokenize(testQuery3);
	std::vector<std::string> result4 = QueryTokenizer::tokenize(testQuery4);

	std::vector<std::string> expectedResult1 = { "assign", "a", ";", "Select", "a", "pattern", "a", "(", "_", ",", "_", ")"};
	std::vector<std::string> expectedResult2 = { "assign", "a", ";", "Select", "a", "pattern", "a", "(", "_", ",", "_\"(a+b)\"_", ")" };
	std::vector<std::string> expectedResult3 = { "assign", "a", ";", "Select", "a", "pattern", "a", "(", "_", ",", "\"(a+b)\"", ")" };
	std::vector<std::string> expectedResult4 = { "assign", "a", ";", "Select", "a", "pattern", "a", "(", "_", ",", "\"(a+b)\"", ")" };


	REQUIRE(result1 == expectedResult1);
	REQUIRE(result2 == expectedResult2);
	REQUIRE(result3 == expectedResult3);
	REQUIRE(result4 == expectedResult4);
}

TEST_CASE("Test QueryTokenizer::collapseTokens") {
    std::vector<std::string> tokens1 = {"_", "\"", "a", "b", "c", "\"", "_"};
    std::vector<std::string> tokens2 = {"_", "\"", "a", "+", "b", "*", "c", "d", "\"", "_"};

    std::vector<std::string> results1 = QueryTokenizer::collapseTokens(tokens1);
    std::vector<std::string> results2 = QueryTokenizer::collapseTokens(tokens2);

    std::vector<std::string> expectedResults1 = {"_\"a b c\"_"};
    std::vector<std::string> expectedResults2 = {"_\"a+b*c d\"_"};

    REQUIRE(results1 == expectedResults1);
    REQUIRE(results2 == expectedResults2);
}

TEST_CASE("Testing tokenizing attrRefs") {
    std::string query1 = "assign a; Select <a, a.procName,a.stmt#> with a.stmt#=8";

	std::vector<std::string> results1 = QueryTokenizer::tokenize(query1);

	std::vector<std::string> expectedResults1 = { "assign", "a", ";", "Select", "<", "a", ",", "a.procName", ",", "a.stmt#", ">", "with", "a.stmt#", "=", "8" };

	REQUIRE(results1 == expectedResults1);
}