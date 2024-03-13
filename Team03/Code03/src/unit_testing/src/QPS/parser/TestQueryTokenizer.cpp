#include "catch.hpp"
#include "qps/QueryTokenizer.h"
#include <iostream>

TEST_CASE("QueryTokenizer::tokenize should remove trailing whitespaces") {
	QueryTokenizer qe;
	std::string testQuery1 = "variable a      ;";
	std::string testQuery2 = "assign     a   ;   Select    a";
	std::string testQuery3 = "procedure   p,   p1; Select     p such      that      Calls(   p,    p1   )    ";

	std::vector<std::vector<std::vector<std::string>>> result1 = qe.tokenize(testQuery1);
	std::vector<std::vector<std::vector<std::string>>> result2 = qe.tokenize(testQuery2);
	std::vector<std::vector<std::vector<std::string>>> result3 = qe.tokenize(testQuery3);

	std::vector<std::vector<std::vector<std::string>>> expectedResult1 = { {{"variable", "a", ";"}}, {}, {} };
	std::vector<std::vector<std::vector<std::string>>> expectedResult2 = { {{"assign", "a", ";"}}, {{"Select", "a"}}, {} };
	std::vector<std::vector<std::vector<std::string>>> expectedResult3 = { {{"procedure", "p", ",", "p1", ";"}}, {{"Select", "p"}}, {{"such", "that", "Calls", "(", "p", ",", "p1", ")"}} };

	REQUIRE(result1 == expectedResult1);
	REQUIRE(result2 == expectedResult2);
	REQUIRE(result3 == expectedResult3);

}

TEST_CASE("QueryTokenizer::tokenize should recognise each punctuation as a separate token") {
	QueryTokenizer qe;
	std::string testQuery1 = "variable a,b,c;";
	std::string testQuery2 = "variable a, b, c;assign d,c;";

	std::vector<std::vector<std::vector<std::string>>> result1 = qe.tokenize(testQuery1);
	std::vector<std::vector<std::vector<std::string>>> result2 = qe.tokenize(testQuery2);

	std::vector<std::vector<std::vector<std::string>>> expectedResult1 = { {{"variable", "a", ",", "b", ",", "c", ";"}}, {}, {} };
	std::vector<std::vector<std::vector<std::string>>> expectedResult2 = { {{"variable", "a", ",", "b", ",", "c", ";"}, {"assign", "d", ",", "c", ";"}}, {}, {} };

	REQUIRE(result1 == expectedResult1);
	REQUIRE(result2 == expectedResult2);
}

TEST_CASE("QueryTokenizer::tokenize should correctly tokenize patterns") {
	QueryTokenizer qe;
	std::string testQuery1 = "assign a; Select a pattern a(_, _)"; // both wildcards
	std::string testQuery2 = "assign a; Select a pattern a(_, _\"(a+b)\"_)"; // partial match
	std::string testQuery3 = "assign a; Select a pattern a(_, \"(a+b)\")"; // complete match
	std::string testQuery4 = "assign a; Select a pattern a(_, \"( a+  b)\")"; // complete match with empty spaces

	std::vector<std::vector<std::vector<std::string>>> result1 = qe.tokenize(testQuery1);
	std::vector<std::vector<std::vector<std::string>>> result2 = qe.tokenize(testQuery2);
	std::vector<std::vector<std::vector<std::string>>> result3 = qe.tokenize(testQuery3);
	std::vector<std::vector<std::vector<std::string>>> result4 = qe.tokenize(testQuery4);

	std::vector<std::vector<std::vector<std::string>>> expectedResult1 = { {{"assign", "a", ";"}}, {{"Select", "a"}}, {{"pattern", "a", "(", "_", ",", "_", ")"}}};
	std::vector<std::vector<std::vector<std::string>>> expectedResult2 = { {{"assign", "a", ";"}}, {{"Select", "a"}}, {{"pattern", "a", "(", "_", ",", "_\"(a+b)\"_", ")"}} };
	std::vector<std::vector<std::vector<std::string>>> expectedResult3 = { {{"assign", "a", ";"}}, {{"Select", "a"}}, {{"pattern", "a", "(", "_", ",", "\"(a+b)\"", ")"}} };
	std::vector<std::vector<std::vector<std::string>>> expectedResult4 = { {{"assign", "a", ";"}}, {{"Select", "a"}}, {{"pattern", "a", "(", "_", ",", "\"( a+  b)\"", ")"}} };


	REQUIRE(result1 == expectedResult1);
	REQUIRE(result2 == expectedResult2);
	REQUIRE(result3 == expectedResult3);
	REQUIRE(result4 == expectedResult4);
}

TEST_CASE("QueryTokenizer::tokenize should correctly split query into lists of tokens, where each list is a part of the query") {
	QueryTokenizer qe;
	std::string testQuery = "variable a; Select a such that Follows(a, _) pattern a(_, _)";

	std::vector<std::vector<std::vector<std::string>>> result = qe.tokenize(testQuery);

	std::vector<std::vector<std::vector<std::string>>> expectedResult = { {{"variable", "a", ";"}}, {{"Select", "a"}}, {{"such", "that", "Follows", "(", "a", ",", "_", ")"}, {"pattern", "a", "(", "_", ",", "_", ")"}} };

	REQUIRE(result == expectedResult);
}

TEST_CASE("QueryTokenizer::tokenize should support synonyms with names that are same as keywords") {
	QueryTokenizer qe;
	std::string testQuery = "variable Select, assign; assign variable; Select Select";

	std::vector<std::vector<std::vector<std::string>>> result = qe.tokenize(testQuery);

	std::vector<std::vector<std::vector<std::string>>> expectedResult = { {{"variable", "Select", ",", "assign", ";"}, {"assign", "variable", ";"}}, {{"Select", "Select"}}, {} };

	REQUIRE(result == expectedResult);
}

TEST_CASE("QueryTokenizer::splitTokens should throw error if clauses are in the wrong order") {
	QueryTokenizer qe;
	std::string testQuery1 = "variable a, b; assign c; Select a such that Follows (a, _) pattern a(_, _)";
	std::string testQuery2 = "variable a, b; Select a assign c; such that Follows (a, _) pattern a(_, _)"; // Declaration after Select
	std::string testQuery3 = "variable a, b; such that Follows (a, _) assign c; Select a  pattern a(_, _)"; // Clause before Declaration
	std::string testQuery4 = "variable a, b; assign c; such that Follows (a, _) pattern a(_, _) Select a"; // Select after clause

	REQUIRE_NOTHROW(qe.tokenize(testQuery1));
	REQUIRE_THROWS(qe.tokenize(testQuery2));
	REQUIRE_THROWS(qe.tokenize(testQuery3));
	REQUIRE_THROWS(qe.tokenize(testQuery4));
}