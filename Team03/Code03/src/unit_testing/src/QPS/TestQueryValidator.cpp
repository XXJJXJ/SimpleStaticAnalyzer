//ai-gen start(gpt, 1, 0)
// prompt: https://chat.openai.com/share/c3dec1ba-84fd-4fdb-ab11-c7f34bf4ef59

#include <catch.hpp>
#include "qps/QueryValidator.h"

QueryValidator validator;

TEST_CASE("Test isLetter method", "[isLetter]") {
	REQUIRE(validator.isLetter("a") == true);
	REQUIRE(validator.isLetter("A") == true);
	REQUIRE(validator.isLetter("1") == false);
	REQUIRE(validator.isLetter("*") == false);
	REQUIRE(validator.isLetter("") == false);
}

TEST_CASE("Test isDigit method", "[isDigit]") {
	REQUIRE(validator.isDigit("0") == true);
	REQUIRE(validator.isDigit("5") == true);
	REQUIRE(validator.isDigit("9") == true);
	REQUIRE(validator.isDigit("10") == false);
	REQUIRE(validator.isDigit("A") == false);
	REQUIRE(validator.isDigit("") == false);
}

TEST_CASE("Test isNzDigit method", "[isNzDigit]") {
	REQUIRE(validator.isNzDigit("1") == true);
	REQUIRE(validator.isNzDigit("2") == true);
	REQUIRE(validator.isNzDigit("9") == true);
	REQUIRE(validator.isNzDigit("0") == false);
	REQUIRE(validator.isNzDigit("10") == false);
	REQUIRE(validator.isNzDigit("A") == false);
	REQUIRE(validator.isNzDigit("") == false);
}

TEST_CASE("Test isInteger method", "[isInteger]") {
	REQUIRE(validator.isInteger("0") == true);
	REQUIRE(validator.isInteger("1") == true);
	REQUIRE(validator.isInteger("9") == true);
	REQUIRE(validator.isInteger("10") == true);
	REQUIRE(validator.isInteger("123") == true);
	REQUIRE(validator.isInteger("01") == false);
	REQUIRE(validator.isInteger("A") == false);
	REQUIRE(validator.isInteger("") == false);
}

TEST_CASE("Test isIdent method", "[isIdent]") {
	REQUIRE(validator.isIdent("variable") == true);
	REQUIRE(validator.isIdent("Variable1") == true);
	REQUIRE(validator.isIdent("123variable") == false);
	REQUIRE(validator.isIdent("_variable") == false);
	REQUIRE(validator.isIdent("123") == false);
	REQUIRE(validator.isIdent("") == false);
}

TEST_CASE("Test isSynonym method", "[isSynonym]") {
	REQUIRE(validator.isSynonym("stmt") == true);
	REQUIRE(validator.isSynonym("variable") == true);
	REQUIRE(validator.isSynonym("read") == true);
	REQUIRE(validator.isSynonym("xyz") == false);
	REQUIRE(validator.isSynonym("") == false);
}

TEST_CASE("Test isStmtRef method", "[isStmtRef]") {
	REQUIRE(validator.isStmtRef("stmt") == true);
	REQUIRE(validator.isStmtRef("_") == true);
	REQUIRE(validator.isStmtRef("10") == true);
	REQUIRE(validator.isStmtRef("xyz") == false);
	REQUIRE(validator.isStmtRef("") == false);
}

TEST_CASE("Test isEntRef method", "[isEntRef]") {
	REQUIRE(validator.isEntRef("stmt") == true);
	REQUIRE(validator.isEntRef("_") == true);
	REQUIRE(validator.isEntRef("\"variable\"") == true);
	//REQUIRE(validator.isEntRef("\"_\"") == true);
	REQUIRE(validator.isEntRef("\"123\"") == false);
	REQUIRE(validator.isEntRef("xyz") == false);
	REQUIRE(validator.isEntRef("") == false);
}
// ai-gen end