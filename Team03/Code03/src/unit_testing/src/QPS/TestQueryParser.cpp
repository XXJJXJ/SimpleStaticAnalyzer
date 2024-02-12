#include "catch.hpp"
#include "qps/QueryParser.h"

TEST_CASE("queryTokenizer should return valid tokens") {
	std::string testString = "variable k; select k;";
	std::vector<std::string> expectedVector = { "variable", "k;", "select", "k;" };

	std::vector<std::string> tokenizedVector = QueryParser::tokenizeString(testString);

	REQUIRE(tokenizedVector == tokenizedVector);
	REQUIRE(tokenizedVector == expectedVector);
};

TEST_CASE("removeSemiColon should remove all instances of ; in string") {
	QueryParser qp;
	std::string testString1 = ";;hE;;L;o";
	std::string testString2 = "v;";
	std::string testString3 = "v";
	std::string expectedString = "hELo";
	std::string expectedString2 = "v";

	std::string output1 = qp.removeSemiColon(testString1);
	std::string output2 = qp.removeSemiColon(testString2);
	std::string output3 = qp.removeSemiColon(testString3);

	REQUIRE(output1 == expectedString);
	REQUIRE(output2 == expectedString2);
	REQUIRE(output3 == expectedString2);
}

TEST_CASE("convertStringToEntityType should produce accurate entity type") {
	
}