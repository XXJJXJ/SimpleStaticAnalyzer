#include "catch.hpp"
#include "qps/QpsManager.h"


TEST_CASE("Milestone 1 failed test cases") {
	QpsManager qm;

	std::string string1 = "stmt s, s1; Select s1 such that Follows(\"s\", s1)";
	std::string string2 = "stmt s, s1; Select s such that Follows* (s, \"s1\")";
	std::string string3 = "assign s, s1; Select s such that pattern s (_, _)";
	std::string string4 = "assign s; Select s pattern s (7, _)";
	std::string string5 = "assign s; Select s pattern s (\"7\", _)";
	std::string string6 = "assign s; Select s pattern s (\"7\", _)";
	std::string string7 = "Select 1v";
	std::string string8 = "constant c; assign a; variable v; Select c such that Uses (a, v) pattern a (_, c)";
	std::string string9 = "stmt s; variable v; Select s such that Modifies (_, v)";
	std::string string10 = "assign a; variable v; constant c; Select a such that Uses (a, c) pattern a (\"8\", _)";

	std::vector<std::string> result1 = qm.processQuery(string1);
	std::vector<std::string> result2 = qm.processQuery(string2);
	std::vector<std::string> result3 = qm.processQuery(string3);
	std::vector<std::string> result4 = qm.processQuery(string4);
	std::vector<std::string> result5 = qm.processQuery(string5);
	std::vector<std::string> result6 = qm.processQuery(string6);
	std::vector<std::string> result7 = qm.processQuery(string7);
	std::vector<std::string> result8 = qm.processQuery(string8);
	std::vector<std::string> result9 = qm.processQuery(string9);
	std::vector<std::string> result10 = qm.processQuery(string10);

	std::vector<std::string> expectedSyntaxError = { "SyntaxError" };

	REQUIRE(result1 == expectedSyntaxError);
	REQUIRE(result2 == expectedSyntaxError);
	REQUIRE(result3 == expectedSyntaxError);
	REQUIRE(result4 == expectedSyntaxError);
	REQUIRE(result5 == expectedSyntaxError);
	REQUIRE(result6 == expectedSyntaxError);
	REQUIRE(result7 == expectedSyntaxError);
	REQUIRE(result8 == expectedSyntaxError);
	REQUIRE(result9 == expectedSyntaxError);
	REQUIRE(result10 == expectedSyntaxError);
}

