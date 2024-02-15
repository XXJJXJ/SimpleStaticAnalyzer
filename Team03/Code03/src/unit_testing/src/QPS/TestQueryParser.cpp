#include "catch.hpp"
#include "qps/QueryParser.h"

TEST_CASE("QueryParser::parse should return a Query object") {
	QueryParser qp;
	std::vector<std::vector<std::string>> tokens = { {"variable", "a", ";"}, {"Select", "a"}, {"such", "that", "Follows", "(", "a", ",", "_", ")"}, {"pattern", "a", "(", "_", ",", "_", ")"} };
	std::shared_ptr<Query> query = qp.parse(tokens);
}