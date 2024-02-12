#include "catch.hpp"
#include "qps/QueryParser.h"

TEST_CASE("queryTokenizer-should-return-valid-tokens") {
	std::string testString = "variable k; select k;";
	std::vector<std::string> expectedVector = { "variable", "k;", "select", "k;" };

	std::vector<std::string> tokenizedVector = QueryParser::tokenizeString(testString);

	REQUIRE(tokenizedVector == tokenizedVector);
	REQUIRE(tokenizedVector == expectedVector);
};