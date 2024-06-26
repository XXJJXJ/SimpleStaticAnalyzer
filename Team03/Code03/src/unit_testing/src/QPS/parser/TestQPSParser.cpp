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
	std::string string7 = "assign a; if i; while w; Select <a, i, w> pattern a(_, _) pattern i(_, _, _) pattern w(_, _)";
	std::string string8 = "assign a; Select a pattern a(1, _)";
	std::string string9 = "while w; variable v; Select w pattern w(v, \"x\")";
	std::string string10 = "if i; variable v; Select i pattern i(v, v, v)";
	std::string string11 = "assign a; Select a such that Modifies(a, _) and a(_,_)";
	std::string string12 = "assign a; Select a pattern a(_,_) and Modifies(a, _)";
    std::string string13 = "assign a, b; Select <a, b> such that Follows(a, b) and not Modifies(a, _) pattern a(_ , _) and not b(_, _)";
    std::string string14 = "assign a, b; Select a pattern a(_, _\"a  +b  *   c\"_)";
    std::string string15 = "assign a, b; Select a pattern a(_, _\"aaa bbb ccc\"_)";
    std::string string16 = "assign a; Select <a, a.varName> with a.stmt#=8 and a.varName=\"varName\" such that Follows(a, _)";
	std::string string17 = "assign a; Select <a, a.stmt#> with not a.stmt#=8 and not a.stmt#=9 such that Follows(a, _)";
    std::string string18 = "assign a; Select a such that not not not Modifies(a, _)";
    std::string string19 = "assign a, b, c, d; Select a with a . stmt# = 1 and b.stmt# = 2 and c. stmt# = 3 and d .stmt# = 4";

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
	std::vector<std::string> result11 = qm.processQuery(string11);
	std::vector<std::string> result12 = qm.processQuery(string12);
	std::vector<std::string> result13 = qm.processQuery(string13);
    std::vector<std::string> result14 = qm.processQuery(string14);
    std::vector<std::string> result15 = qm.processQuery(string15);
	std::vector<std::string> result16 = qm.processQuery(string16);
	std::vector<std::string> result17 = qm.processQuery(string17);
    std::vector<std::string> result18 = qm.processQuery(string18);
    std::vector<std::string> result19 = qm.processQuery(string19);

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
	REQUIRE(result8 == expectedSyntaxError);
	REQUIRE(result9 == expectedSemanticError);
	REQUIRE(result10 == expectedSyntaxError);
	REQUIRE(result11 == expectedSyntaxError);
	REQUIRE(result12 == expectedSemanticError);
	REQUIRE(result13 != expectedSyntaxError);
	REQUIRE(result13 != expectedSemanticError);
    REQUIRE(result14 != expectedSyntaxError);
    REQUIRE(result14 != expectedSemanticError);
    REQUIRE(result15 == expectedSyntaxError);
    REQUIRE(result16 == expectedSemanticError);
    REQUIRE(result17 != expectedSyntaxError);
    REQUIRE(result17 != expectedSemanticError);
    REQUIRE(result18 == expectedSyntaxError);
    REQUIRE(result19 != expectedSyntaxError);
    REQUIRE(result19 != expectedSemanticError);
}

