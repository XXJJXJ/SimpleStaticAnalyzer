#include "catch.hpp"
#include "sp/sp.h"

TEST_CASE("1st SP Test") {
	Sp sp = Sp();
	bool result = sp.ProcessSIMPLE("input.txt");
	REQUIRE(result);
}