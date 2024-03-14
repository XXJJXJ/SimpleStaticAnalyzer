#include "catch.hpp"
#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BaseTable.h"
#include "qps/entity/clause/WhilePatternPredicate.h"
#include "../fakeEntities/FakeQueryManager.cpp"
#include "../fakeEntities/MockEntity.cpp" // Assuming MockEntity is in this file

TEST_CASE("WhilePatternPredicate comprehensive test suite", "[WhilePatternPredicate]") {
    FakeQueryManager qm;
    shared_ptr<MockEntity> varX = make_shared<MockEntity>("x", EntityType::Variable);
    shared_ptr<MockEntity> varY = make_shared<MockEntity>("y", EntityType::Variable);
    shared_ptr<MockEntity> whileStmt1 = make_shared<MockEntity>("1", EntityType::While);
    shared_ptr<MockEntity> whileStmt2 = make_shared<MockEntity>("2", EntityType::While);
    shared_ptr<MockEntity> whileStmt3 = make_shared<MockEntity>("3", EntityType::While);

    qm.addFakeWhilePattern(whileStmt1, varX);
    qm.addFakeWhilePattern(whileStmt2, varX);
    qm.addFakeWhilePattern(whileStmt3, varY);

    Synonym whileSyn(EntityType::While, "i");

    SECTION("Input validity checks") {
        SECTION("Valid While Synonym and Variable EntityRef as synonym") {
            Synonym varSyn(EntityType::Variable, "v");
            REQUIRE_NOTHROW(WhilePatternPredicate(whileSyn, varSyn));
        }

        SECTION("Valid While Synonym and Variable EntityRef as string") {
            EntityRef varRef = std::string("x");
            REQUIRE_NOTHROW(WhilePatternPredicate(whileSyn, varRef));
        }

        SECTION("Valid While Synonym and wildcard EntityRef") {
            EntityRef wildcard = "_";
            REQUIRE_NOTHROW(WhilePatternPredicate(whileSyn, wildcard));
        }

        SECTION("Invalid While Synonym (using Assign)") {
            Synonym assignSyn(EntityType::Assign, "a");
            EntityRef varRef = std::string("x");
            REQUIRE_THROWS_AS(WhilePatternPredicate(assignSyn, varRef), SemanticErrorException);
        }

        SECTION("Invalid EntityRef (using Procedure name as synonym)") {
            Synonym procSyn(EntityType::Procedure, "p");
            REQUIRE_THROWS_AS(WhilePatternPredicate(whileSyn, procSyn), SemanticErrorException);
        }
    }

    SECTION("Table content verification") {
        SECTION("EntityRef as specific variable name") {
            EntityRef varRef = std::string("x");
            WhilePatternPredicate whilePatternPred(whileSyn, varRef);
            auto resultTable = static_pointer_cast<HeaderTable>(whilePatternPred.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"1", "2"};
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
            REQUIRE(resultTable->getColumnCount() == 1);
            REQUIRE(resultTable->getHeaders().begin()->get()->getName() == "i");
        }

        SECTION("EntityRef as wildcard") {
            EntityRef wildcard = "_";
            WhilePatternPredicate whilePatternPredWildcard(whileSyn, wildcard);
            auto resultTable = static_pointer_cast<HeaderTable>(whilePatternPredWildcard.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"1", "2", "3"};
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
            REQUIRE(resultTable->getColumnCount() == 1);
            REQUIRE(resultTable->getHeaders().begin()->get()->getName() == "i");
        }

        SECTION("EntityRef as synonym of type Variable") {
            Synonym varSyn(EntityType::Variable, "v");
            WhilePatternPredicate whilePatternPredSyn(whileSyn, varSyn);
            auto resultTable = static_pointer_cast<HeaderTable>(whilePatternPredSyn.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"1 x", "2 x", "3 y"};
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
            REQUIRE(resultTable->getColumnCount() == 2);
        }
    }

    SECTION("Complex scenario with various entRef types") {
        // Setup additional mock entities for a complex scenario
        shared_ptr<MockEntity> varZ = make_shared<MockEntity>("z", EntityType::Variable);
        shared_ptr<MockEntity> whileStmt4 = make_shared<MockEntity>("4", EntityType::While);
        shared_ptr<MockEntity> whileStmt5 = make_shared<MockEntity>("5", EntityType::While);
        // Adding patterns involving new variable 'z'
        qm.addFakeWhilePattern(whileStmt4, varZ);
        qm.addFakeWhilePattern(whileStmt5, varZ);
        qm.addFakeWhilePattern(whileStmt5, varY);

        // Test with specific variable name 'y'
        SECTION("EntityRef as specific variable name 'y'") {
            EntityRef varRef = std::string("y");
            WhilePatternPredicate whilePatternPred(whileSyn, varRef);
            auto resultTable = static_pointer_cast<HeaderTable>(whilePatternPred.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"3", "5"}; // Only '1' and '2' use 'x'
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
        }

        // Test with wildcard, expecting all while statements to be included
        SECTION("EntityRef as wildcard") {
            EntityRef wildcard = "_";
            WhilePatternPredicate whilePatternPredWildcard(whileSyn, wildcard);
            auto resultTable = static_pointer_cast<HeaderTable>(whilePatternPredWildcard.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"1", "2", "3", "4", "5"};
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
        }

        // Test with a synonym of type Variable, which should include all variables associated with while statements
        SECTION("EntityRef as synonym of type Variable 'v'") {
            Synonym varSyn(EntityType::Variable, "v");
            WhilePatternPredicate whilePatternPredSyn(whileSyn, varSyn);
            auto resultTable = static_pointer_cast<HeaderTable>(whilePatternPredSyn.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"1 x", "2 x", "3 y", "4 z", "5 z", "5 y"};
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
        }

        // Test with a specific variable name 'z', expecting to filter only while statements that use 'z'
        SECTION("EntityRef as specific variable name 'z'") {
            EntityRef varRef = std::string("z");
            WhilePatternPredicate whilePatternPred(whileSyn, varRef);
            auto resultTable = static_pointer_cast<HeaderTable>(whilePatternPred.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"4", "5"}; // Only '4' and '5' use 'z'
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
        }
    }

}
