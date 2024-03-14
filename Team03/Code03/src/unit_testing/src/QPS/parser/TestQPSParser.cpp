#include "catch.hpp"
#include "qps/QpsManager.h"

// Used for debugging syntax or semantic errors in whole query strings

TEST_CASE("Milestone 1 failed test cases") {
	QpsManager qm;

	std::string string1 = "stmt s, s1; Select s1 such that Follows(\"s\", s1)";
	std::string string2 = "stmt s, s1; Select s such that Follows* (s, \"s1\")";
	std::string string3 = "assign s, s1; Select s such that pattern s (_, _)";
	std::string string4 = "assign s; Select s pattern s (7, _)";
	std::string string5 = "assign s; Select s pattern s (\"7\", _)";
	std::string string6 = "Select 1v";
	std::string string7 = "constant c; assign a; variable v; Select c such that Uses (a, v) pattern a (_, c)";
	std::string string8 = "stmt s; variable v; Select s such that Modifies (_, v)";
	std::string string9 = "assign a; variable v; constant c; Select a such that Uses (a, c) pattern a (\"8\", _)";

    std::vector<std::string> result1 = qm.processQuery(string1);
	std::vector<std::string> result2 = qm.processQuery(string2);
	std::vector<std::string> result3 = qm.processQuery(string3);
	std::vector<std::string> result4 = qm.processQuery(string4);
	std::vector<std::string> result5 = qm.processQuery(string5);
	std::vector<std::string> result6 = qm.processQuery(string6);
	std::vector<std::string> result7 = qm.processQuery(string7);
	std::vector<std::string> result8 = qm.processQuery(string8);
	std::vector<std::string> result9 = qm.processQuery(string9);

    std::vector<std::string> expectedSyntaxError = { "SyntaxError" };
    std::vector<std::string> expectedSemanticError = { "SemanticError" };

    REQUIRE(result1 == expectedSyntaxError);
	REQUIRE(result2 == expectedSyntaxError);
	REQUIRE(result3 == expectedSyntaxError);
	REQUIRE(result4 == expectedSyntaxError);
	REQUIRE(result5 == expectedSyntaxError);
	REQUIRE(result6 == expectedSyntaxError);
	REQUIRE(result7 == expectedSyntaxError);
	REQUIRE(result8 == expectedSemanticError);
	REQUIRE(result9 == expectedSyntaxError);
}

TEST_CASE("Debugging whole strings") {
    QpsManager qm;
    std::string string1 = "assign a; variable v; constant c; Select a such that Uses (a, c) pattern a (\"8\", _) invalid words";
    std::string string2 = "stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; procedure p, q; constant c; read re; print pn; call cl; Select a pattern a(_, _\"x+y*v \"_)";
	std::string string3 = "assign a, b; Select a Select <a, b>";
	std::string string4 = "Select BOOLEAN";
	std::string string5 = "assign a; Select a such that Calls(a, a)";
	std::string string6 = "procedure a; Select a such that Calls(a, a)";
	std::string string7 = "assign a; if i; while w; Select <a, i, w> pattern a(_, _) pattern i(_, _, _) pattern w(_, )";

    std::vector<std::string> result1 = qm.processQuery(string1);
    std::vector<std::string> result2 = qm.processQuery(string2);
	std::vector<std::string> result3 = qm.processQuery(string3);
	std::vector<std::string> result4 = qm.processQuery(string4);
	std::vector<std::string> result5 = qm.processQuery(string5);
	std::vector<std::string> result6 = qm.processQuery(string6);
	std::vector<std::string> result7 = qm.processQuery(string6);

    std::vector<std::string> expectedSyntaxError = { "SyntaxError" };
    std::vector<std::string> expectedSemanticError = { "SemanticError" };

    REQUIRE(result1 == expectedSyntaxError);
    REQUIRE(result2 != expectedSyntaxError);
    REQUIRE(result2 != expectedSemanticError);
	REQUIRE(result3 == expectedSyntaxError);
	REQUIRE(result4 != expectedSyntaxError);
	REQUIRE(result4 != expectedSemanticError);
	REQUIRE(result5 == expectedSemanticError);
	REQUIRE(result6 != expectedSyntaxError);
	REQUIRE(result6 != expectedSemanticError);
	REQUIRE(result7 != expectedSyntaxError);
	REQUIRE(result7 != expectedSemanticError);
}

