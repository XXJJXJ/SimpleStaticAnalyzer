#include <catch.hpp>
#include "qps/util/QueryTokenValidator.h"

//ai-gen start(gpt, 2, e)
// prompt: https://chat.openai.com/share/c3dec1ba-84fd-4fdb-ab11-c7f34bf4ef59

TEST_CASE("Test isLetter method", "[isLetter]") {
    REQUIRE(QueryTokenValidator::isLetter("a"));
    REQUIRE(QueryTokenValidator::isLetter("A"));
    REQUIRE(!QueryTokenValidator::isLetter("1"));
    REQUIRE(!QueryTokenValidator::isLetter("*"));
    REQUIRE(!QueryTokenValidator::isLetter(""));
}

TEST_CASE("Test isDigit method", "[isDigit]") {
    REQUIRE(QueryTokenValidator::isDigit("0"));
    REQUIRE(QueryTokenValidator::isDigit("5"));
    REQUIRE(QueryTokenValidator::isDigit("9"));
    REQUIRE(!QueryTokenValidator::isDigit("10"));
    REQUIRE(!QueryTokenValidator::isDigit("A"));
    REQUIRE(!QueryTokenValidator::isDigit(""));
}

TEST_CASE("Test isNzDigit method", "[isNzDigit]") {
    REQUIRE(QueryTokenValidator::isNzDigit("1"));
    REQUIRE(QueryTokenValidator::isNzDigit("2"));
    REQUIRE(QueryTokenValidator::isNzDigit("9"));
    REQUIRE(!QueryTokenValidator::isNzDigit("0"));
    REQUIRE(!QueryTokenValidator::isNzDigit("10"));
    REQUIRE(!QueryTokenValidator::isNzDigit("A"));
    REQUIRE(!QueryTokenValidator::isNzDigit(""));
}

// Definition of integer: 0 | NZDIGIT ( DIGIT )* - no leading zero
TEST_CASE("Test isInteger method", "[isInteger]") {
    REQUIRE(QueryTokenValidator::isInteger("0"));
    REQUIRE(QueryTokenValidator::isInteger("1"));
    REQUIRE(QueryTokenValidator::isInteger("9"));
    REQUIRE(QueryTokenValidator::isInteger("10"));
    REQUIRE(QueryTokenValidator::isInteger("123"));
    REQUIRE(!QueryTokenValidator::isInteger("01"));
    REQUIRE(!QueryTokenValidator::isInteger("A"));
    REQUIRE(!QueryTokenValidator::isInteger("Long_Invalid_Chars"));
    REQUIRE(!QueryTokenValidator::isInteger("12Mix0fCh@rs"));
    REQUIRE(!QueryTokenValidator::isInteger(""));
}

// Definition of identifier (IDENT): LETTER ( LETTER | DIGIT )*
TEST_CASE("Test isIdent method", "[isIdent]") {
    REQUIRE(QueryTokenValidator::isIdent("variable"));
    REQUIRE(QueryTokenValidator::isIdent("Variable1"));
    REQUIRE(!QueryTokenValidator::isIdent("123variable"));
    REQUIRE(!QueryTokenValidator::isIdent("_variable"));
    REQUIRE(!QueryTokenValidator::isIdent("123"));
    REQUIRE(!QueryTokenValidator::isIdent(""));
}

// Definition of synonym: IDENT
TEST_CASE("Test isSynonym method", "[isSynonym]") {
    REQUIRE(QueryTokenValidator::isSynonym("stmt"));
    REQUIRE(QueryTokenValidator::isSynonym("variable"));
    REQUIRE(QueryTokenValidator::isSynonym("read"));
    REQUIRE(QueryTokenValidator::isSynonym("xyz"));
    REQUIRE(!QueryTokenValidator::isSynonym(""));
}

// Definition of stmtRef: synonym | '_' | INTEGER
TEST_CASE("Test isStmtRef method", "[isStmtRef]") {
    REQUIRE(QueryTokenValidator::isStmtRef("stmt"));
    REQUIRE(QueryTokenValidator::isStmtRef("_"));
    REQUIRE(QueryTokenValidator::isStmtRef("10"));
    REQUIRE(QueryTokenValidator::isStmtRef("xyz"));
    REQUIRE(!QueryTokenValidator::isStmtRef(""));
}

TEST_CASE("Test isEntRef method", "[isEntRef]") {
    REQUIRE(QueryTokenValidator::isEntRef("stmt"));
    REQUIRE(QueryTokenValidator::isEntRef("_"));
    REQUIRE(QueryTokenValidator::isEntRef("\"variable\""));
    REQUIRE(!QueryTokenValidator::isEntRef("\"_\""));
    REQUIRE(!QueryTokenValidator::isEntRef("\"123\""));
    REQUIRE(QueryTokenValidator::isEntRef("xyz"));
    REQUIRE(!QueryTokenValidator::isEntRef(""));
}
// ai-gen end

TEST_CASE("Test isExpr", "[isExpr]") {
    REQUIRE(QueryTokenValidator::isExpr("x+y"));
    REQUIRE(QueryTokenValidator::isExpr("a-b"));
    REQUIRE(QueryTokenValidator::isExpr("a+b-c"));
    REQUIRE(QueryTokenValidator::isExpr("a*b+c"));
    REQUIRE(QueryTokenValidator::isExpr("(a+b)*c"));
    REQUIRE(QueryTokenValidator::isExpr("a+b*(c-d)"));
    REQUIRE(QueryTokenValidator::isExpr("a"));
    REQUIRE(QueryTokenValidator::isExpr("(a)"));
    REQUIRE(QueryTokenValidator::isExpr("2"));
    REQUIRE(QueryTokenValidator::isExpr("x+y*v"));

    REQUIRE_FALSE(QueryTokenValidator::isExpr(""));
    REQUIRE_FALSE(QueryTokenValidator::isExpr("a+b+c+"));
    REQUIRE_FALSE(QueryTokenValidator::isExpr("*a+b"));
    REQUIRE_FALSE(QueryTokenValidator::isExpr("a b c"));
}

TEST_CASE("Test isTerm", "[isTerm]") {
    REQUIRE(QueryTokenValidator::isTerm("x*y"));
    REQUIRE(QueryTokenValidator::isTerm("a/b"));
    REQUIRE(QueryTokenValidator::isTerm("a%b"));
    REQUIRE(QueryTokenValidator::isTerm("a*b/c"));
    REQUIRE(QueryTokenValidator::isTerm("(a+b)*c"));
    REQUIRE(QueryTokenValidator::isTerm("a*b*(c-d)"));
    REQUIRE(QueryTokenValidator::isTerm("a"));
    REQUIRE(QueryTokenValidator::isTerm("(a)"));

    REQUIRE_FALSE(QueryTokenValidator::isTerm(""));
    REQUIRE_FALSE(QueryTokenValidator::isTerm("a*b*c*"));
    REQUIRE_FALSE(QueryTokenValidator::isTerm("+a*b"));
}

TEST_CASE("Test isFactor", "[isFactor]") {
    REQUIRE(QueryTokenValidator::isFactor("x"));
    REQUIRE(QueryTokenValidator::isFactor("y"));
    REQUIRE(QueryTokenValidator::isFactor("a"));
    REQUIRE(QueryTokenValidator::isFactor("abc123"));
    REQUIRE(QueryTokenValidator::isFactor("(a+b)"));

    REQUIRE_FALSE(QueryTokenValidator::isFactor(""));
    REQUIRE_FALSE(QueryTokenValidator::isFactor("a+b"));
    REQUIRE_FALSE(QueryTokenValidator::isFactor("(a+b"));
    REQUIRE_FALSE(QueryTokenValidator::isFactor("a+b)"));
}

TEST_CASE("Test QueryTokenValidator::isRef") {
    SECTION("Valid refs") {
        std::string token1 = "123";
        std::string token2 = "validSynonym.procName";
        std::string token3 = "validSynonym.varName";
        std::string token4 = "validSynonym.value";
        std::string token5 = "validSynonym.stmt#";
        std::string token6 = "\"validIdent\"";

        REQUIRE(QueryTokenValidator::isRef(token1));
        REQUIRE(QueryTokenValidator::isRef(token2));
        REQUIRE(QueryTokenValidator::isRef(token3));
        REQUIRE(QueryTokenValidator::isRef(token4));
        REQUIRE(QueryTokenValidator::isRef(token5));
        REQUIRE(QueryTokenValidator::isRef(token6));
    }

    SECTION("Invalid refs") {
        std::string token1 = "123Invalid";
        std::string token2 = "validSynonym.invalidAttribute";
        std::string token3 = "123InvalidSynonym.stmt#";
        std::string token4 = "\"123InvalidIdent\"";

        REQUIRE(!QueryTokenValidator::isRef(token1));
        REQUIRE(!QueryTokenValidator::isRef(token2));
        REQUIRE(!QueryTokenValidator::isRef(token3));
        REQUIRE(!QueryTokenValidator::isRef(token4));
    }
}