#include <catch.hpp>
#include "qps/EntityTypeConverter.h"

TEST_CASE("Valid conversions from string to EntityType", "[entity_converter]") {
    REQUIRE(EntityTypeConverter::getEnumFromString("stmt") == EntityType::Stmt);
    REQUIRE(EntityTypeConverter::getEnumFromString("read") == EntityType::Read);
    REQUIRE(EntityTypeConverter::getEnumFromString("print") == EntityType::Print);
    REQUIRE(EntityTypeConverter::getEnumFromString("call") == EntityType::Call);
    REQUIRE(EntityTypeConverter::getEnumFromString("while") == EntityType::While);
    REQUIRE(EntityTypeConverter::getEnumFromString("if") == EntityType::If);
    REQUIRE(EntityTypeConverter::getEnumFromString("assign") == EntityType::Assign);
    REQUIRE(EntityTypeConverter::getEnumFromString("variable") == EntityType::Variable);
    REQUIRE(EntityTypeConverter::getEnumFromString("constant") == EntityType::Constant);
    REQUIRE(EntityTypeConverter::getEnumFromString("procedure") == EntityType::Procedure);
}

TEST_CASE("Invalid conversions from string to EntityType", "[entity_converter]") {
    REQUIRE(EntityTypeConverter::getEnumFromString("invalid") == EntityType::Unknown);
    REQUIRE(EntityTypeConverter::getEnumFromString("") == EntityType::Unknown);
}

TEST_CASE("EntityType to string conversions", "[entity_converter]") {
    REQUIRE(EntityTypeConverter::getStringFromEnum(EntityType::Stmt) == "stmt");
    REQUIRE(EntityTypeConverter::getStringFromEnum(EntityType::Read) == "read");
    REQUIRE(EntityTypeConverter::getStringFromEnum(EntityType::Print) == "print");
    REQUIRE(EntityTypeConverter::getStringFromEnum(EntityType::Call) == "call");
    REQUIRE(EntityTypeConverter::getStringFromEnum(EntityType::While) == "while");
    REQUIRE(EntityTypeConverter::getStringFromEnum(EntityType::If) == "if");
    REQUIRE(EntityTypeConverter::getStringFromEnum(EntityType::Assign) == "assign");
    REQUIRE(EntityTypeConverter::getStringFromEnum(EntityType::Variable) == "variable");
    REQUIRE(EntityTypeConverter::getStringFromEnum(EntityType::Constant) == "constant");
    REQUIRE(EntityTypeConverter::getStringFromEnum(EntityType::Procedure) == "procedure");
    REQUIRE(EntityTypeConverter::getStringFromEnum(EntityType::Unknown) == "Unknown");
}