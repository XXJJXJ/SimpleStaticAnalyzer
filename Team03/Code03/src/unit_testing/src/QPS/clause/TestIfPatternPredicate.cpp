#include "catch.hpp"
#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BaseTable.h"
#include "qps/entity/clause/IfPatternPredicate.h"
#include "../fakeEntities/FakeQueryManager.cpp"
#include "../fakeEntities/MockEntity.cpp" // Assuming MockEntity is in this file

TEST_CASE("IfPatternPredicate comprehensive test suite", "[IfPatternPredicate]") {
    FakeQueryManager qm;
    shared_ptr<MockEntity> varX = make_shared<MockEntity>("x", EntityType::Variable);
    shared_ptr<MockEntity> varY = make_shared<MockEntity>("y", EntityType::Variable);
    shared_ptr<MockEntity> ifStmt1 = make_shared<MockEntity>("1", EntityType::If);
    shared_ptr<MockEntity> ifStmt2 = make_shared<MockEntity>("2", EntityType::If);
    shared_ptr<MockEntity> ifStmt3 = make_shared<MockEntity>("3", EntityType::If);

    qm.addFakeIfPattern(ifStmt1, varX);
    qm.addFakeIfPattern(ifStmt2, varX);
    qm.addFakeIfPattern(ifStmt3, varY);

    Synonym ifSyn(EntityType::If, "i");

    SECTION("Input validity checks") {
        SECTION("Valid If Synonym and Variable EntityRef as synonym") {
            Synonym varSyn(EntityType::Variable, "v");
            REQUIRE_NOTHROW(IfPatternPredicate(ifSyn, varSyn));
        }

        SECTION("Valid If Synonym and Variable EntityRef as string") {
            EntityRef varRef = std::string("x");
            REQUIRE_NOTHROW(IfPatternPredicate(ifSyn, varRef));
        }

        SECTION("Valid If Synonym and wildcard EntityRef") {
            EntityRef wildcard = "_";
            REQUIRE_NOTHROW(IfPatternPredicate(ifSyn, wildcard));
        }

        SECTION("Invalid If Synonym (using Assign)") {
            Synonym assignSyn(EntityType::Assign, "a");
            EntityRef varRef = std::string("x");
            REQUIRE_THROWS_AS(IfPatternPredicate(assignSyn, varRef), SemanticErrorException);
        }

        SECTION("Invalid EntityRef (using Procedure name as synonym)") {
            Synonym procSyn(EntityType::Procedure, "p");
            REQUIRE_THROWS_AS(IfPatternPredicate(ifSyn, procSyn), SemanticErrorException);
        }
    }

    SECTION("Table content verification") {
        SECTION("EntityRef as specific variable name") {
            EntityRef varRef = std::string("x");
            IfPatternPredicate ifPatternPred(ifSyn, varRef);
            auto resultTable = static_pointer_cast<HeaderTable>(ifPatternPred.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"1", "2"};
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
            REQUIRE(resultTable->getColumnCount() == 1);
            REQUIRE(resultTable->getHeaders().begin()->get()->getName() == "i");
        }

        SECTION("EntityRef as wildcard") {
            EntityRef wildcard = "_";
            IfPatternPredicate ifPatternPredWildcard(ifSyn, wildcard);
            auto resultTable = static_pointer_cast<HeaderTable>(ifPatternPredWildcard.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"1", "2", "3"};
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
            REQUIRE(resultTable->getColumnCount() == 1);
            REQUIRE(resultTable->getHeaders().begin()->get()->getName() == "i");
        }

        SECTION("EntityRef as synonym of type Variable") {
            Synonym varSyn(EntityType::Variable, "v");
            IfPatternPredicate ifPatternPredSyn(ifSyn, varSyn);
            auto resultTable = static_pointer_cast<HeaderTable>(ifPatternPredSyn.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"1 x", "2 x", "3 y"};
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
            REQUIRE(resultTable->getColumnCount() == 2);
        }
    }

    SECTION("Complex scenario with various entRef types") {
        // This section would repeat similar tests but considering a mix of conditions
        // to validate the behavior comprehensively across different setups.
    }

    SECTION("Complex scenario with various entRef types") {
        // Setup additional mock entities for a complex scenario
        shared_ptr<MockEntity> varZ = make_shared<MockEntity>("z", EntityType::Variable);
        shared_ptr<MockEntity> ifStmt4 = make_shared<MockEntity>("4", EntityType::If);
        shared_ptr<MockEntity> ifStmt5 = make_shared<MockEntity>("5", EntityType::If);
        // Adding patterns involving new variable 'z'
        qm.addFakeIfPattern(ifStmt4, varZ);
        qm.addFakeIfPattern(ifStmt5, varZ);
        qm.addFakeIfPattern(ifStmt5, varY);

        // Test with specific variable name 'y'
        SECTION("EntityRef as specific variable name 'y'") {
            EntityRef varRef = std::string("y");
            IfPatternPredicate ifPatternPred(ifSyn, varRef);
            auto resultTable = static_pointer_cast<HeaderTable>(ifPatternPred.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"3", "5"}; // Only 'if1' and 'if2' use 'x'
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
        }

        // Test with wildcard, expecting all if statements to be included
        SECTION("EntityRef as wildcard") {
            EntityRef wildcard = "_";
            IfPatternPredicate ifPatternPredWildcard(ifSyn, wildcard);
            auto resultTable = static_pointer_cast<HeaderTable>(ifPatternPredWildcard.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"1", "2", "3", "4", "5"};
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
        }

        // Test with a synonym of type Variable, which should include all variables associated with if statements
        SECTION("EntityRef as synonym of type Variable 'v'") {
            Synonym varSyn(EntityType::Variable, "v");
            IfPatternPredicate ifPatternPredSyn(ifSyn, varSyn);
            auto resultTable = static_pointer_cast<HeaderTable>(ifPatternPredSyn.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"1 x", "2 x", "3 y", "4 z", "5 z", "5 y"};
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
        }

        // Test with a specific variable name 'z', expecting to filter only if statements that use 'z'
        SECTION("EntityRef as specific variable name 'z'") {
            EntityRef varRef = std::string("z");
            IfPatternPredicate ifPatternPred(ifSyn, varRef);
            auto resultTable = static_pointer_cast<HeaderTable>(ifPatternPred.getResultTable(qm));
            auto result = resultTable->toStrings();
            std::unordered_set<std::string> expected = {"4", "5"}; // Only 'if4' and 'if5' use 'z'
            REQUIRE(resultTable != nullptr);
            REQUIRE(result == expected);
        }
    }

}
