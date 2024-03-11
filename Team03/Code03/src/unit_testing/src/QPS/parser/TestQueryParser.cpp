#include "catch.hpp"
#include "qps/QueryParser.h"

TEST_CASE("QueryParser::parse should return a Query object") {
	QueryParser qp;
	std::vector<std::vector<std::vector<std::string>>> tokens = { {{"stmt", "s"}, {"assign", "a"}}, {{"s"}}, {{"Follows", "s", "_"}, {"pattern", "a", "_", "_"}} };
	REQUIRE_NOTHROW(qp.parse(tokens));
	std::vector<std::vector<std::vector<std::string>>> tokens2 = { {{"constant", "c"}}, {{"c"}}, {} };
    REQUIRE_NOTHROW(qp.parse(tokens2));
}