#include "catch.hpp"
#include "qps/QueryTokenizer.h"

TEST_CASE("QueryTokenizer::tokenize should remove trailing whitespaces") {
	QueryTokenizer qe;
	std::string testQuery1 = "variable a      ;";
	std::string testQuery2 = "assign     a   ;   Select    a";

	std::vector<std::vector<std::vector<std::string>>> result1 = qe.tokenize(testQuery1);
	std::vector<std::vector<std::vector<std::string>>> result2 = qe.tokenize(testQuery2);

	std::vector<std::vector<std::vector<std::string>>> expectedResult1 = { {{"variable", "a", ";"}}, {}, {} };
	std::vector<std::vector<std::vector<std::string>>> expectedResult2 = { {{"assign", "a", ";"}}, {{"Select", "a"}}, {} };

	REQUIRE(result1 == expectedResult1);
	REQUIRE(result2 == expectedResult2);
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