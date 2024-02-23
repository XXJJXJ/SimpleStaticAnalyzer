//ai-gen start(gpt, 2, e)
// prompt: https://chat.openai.com/share/c3dec1ba-84fd-4fdb-ab11-c7f34bf4ef59

#include <catch.hpp>
#include "qps/QueryValidator.h"

QueryValidator validator;

TEST_CASE("Test isLetter method", "[isLetter]") {
	REQUIRE(validator.isLetter("a"));
	REQUIRE(validator.isLetter("A"));
	REQUIRE(!validator.isLetter("1"));
	REQUIRE(!validator.isLetter("*"));
	REQUIRE(!validator.isLetter(""));
}

TEST_CASE("Test isDigit method", "[isDigit]") {
	REQUIRE(validator.isDigit("0"));
	REQUIRE(validator.isDigit("5"));
	REQUIRE(validator.isDigit("9"));
	REQUIRE(!validator.isDigit("10"));
	REQUIRE(!validator.isDigit("A"));
	REQUIRE(!validator.isDigit(""));
}

TEST_CASE("Test isNzDigit method", "[isNzDigit]") {
	REQUIRE(validator.isNzDigit("1"));
	REQUIRE(validator.isNzDigit("2"));
	REQUIRE(validator.isNzDigit("9"));
	REQUIRE(!validator.isNzDigit("0"));
	REQUIRE(!validator.isNzDigit("10"));
	REQUIRE(!validator.isNzDigit("A"));
	REQUIRE(!validator.isNzDigit(""));
}

// Definition of integer: 0 | NZDIGIT ( DIGIT )* - no leading zero
TEST_CASE("Test isInteger method", "[isInteger]") {
	REQUIRE(validator.isInteger("0"));
	REQUIRE(validator.isInteger("1"));
	REQUIRE(validator.isInteger("9"));
	REQUIRE(validator.isInteger("10"));
	REQUIRE(validator.isInteger("123"));
	REQUIRE(!validator.isInteger("01"));
	REQUIRE(!validator.isInteger("A"));
    REQUIRE(!validator.isInteger("aBcSDSWdds"));
    REQUIRE(!validator.isInteger("01fscd43j2d"));
	REQUIRE(!validator.isInteger(""));
}

// Definition of identifier (IDENT): LETTER ( LETTER | DIGIT )*
TEST_CASE("Test isIdent method", "[isIdent]") {
	REQUIRE(validator.isIdent("variable"));
	REQUIRE(validator.isIdent("Variable1"));
	REQUIRE(!validator.isIdent("123variable"));
	REQUIRE(!validator.isIdent("_variable"));
	REQUIRE(!validator.isIdent("123"));
	REQUIRE(!validator.isIdent(""));
}

// Definition of synonym: IDENT
TEST_CASE("Test isSynonym method", "[isSynonym]") {
	REQUIRE(validator.isSynonym("stmt"));
	REQUIRE(validator.isSynonym("variable"));
	REQUIRE(validator.isSynonym("read"));
	REQUIRE(validator.isSynonym("xyz"));
	REQUIRE(!validator.isSynonym(""));
}

// Definition of stmtRef: synonym | '_' | INTEGER
TEST_CASE("Test isStmtRef method", "[isStmtRef]") {
	REQUIRE(validator.isStmtRef("stmt"));
	REQUIRE(validator.isStmtRef("_"));
	REQUIRE(validator.isStmtRef("10"));
	REQUIRE(validator.isStmtRef("xyz"));
	REQUIRE(!validator.isStmtRef(""));
}

TEST_CASE("Test isEntRef method", "[isEntRef]") {
	REQUIRE(validator.isEntRef("stmt"));
	REQUIRE(validator.isEntRef("_"));
	REQUIRE(validator.isEntRef("\"variable\""));
	REQUIRE(!validator.isEntRef("\"_\""));
	REQUIRE(!validator.isEntRef("\"123\""));
	REQUIRE(validator.isEntRef("xyz"));
	REQUIRE(!validator.isEntRef(""));
}
// ai-gen end