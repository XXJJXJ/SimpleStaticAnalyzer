#include "catch.hpp"
#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/clause/AssignPatternPredicate.h"

#include "../fakeEntities/FakeQueryManager.cpp"

TEST_CASE("AssignPatternPredicate with specific variable and exact match") {
    FakeQueryManager qm;
    auto variableX = std::make_shared<Variable>("x");
    auto variableY = std::make_shared<Variable>("y");
    auto variableZ = std::make_shared<Variable>("z");
    auto variableW = std::make_shared<Variable>("w");

    auto variableSynonym = std::make_shared<Synonym>(EntityType::Variable, "v");
    auto variableWildcard = "_";

    auto assignStmt1 = std::make_shared<AssignStatement>(1, variableX, "proc");
    auto assignStmt2 = std::make_shared<AssignStatement>(2, variableY, "x+2");
    auto assignStmt3 = std::make_shared<AssignStatement>(3, variableZ, "y+2");
    auto assignStmt4 = std::make_shared<AssignStatement>(4, variableX, "y+2");
    auto assignStmt5 = std::make_shared<AssignStatement>(5, variableY, "z+2");
    auto assignSynonym = std::make_shared<Synonym>(EntityType::Assign, "a");



    SECTION("Works for Synonym lhs") {
        AssignPatternPredicate predicate(*assignSynonym, *variableSynonym, "unused");
        qm.setFakeAssignsWithPattern({assignStmt1, assignStmt2, assignStmt3, assignStmt4, assignStmt5});
        qm.setAllFakeVariable({variableX, variableY, variableZ, variableW});
        auto table = static_pointer_cast<HeaderTable>(predicate.getTable(qm));
        REQUIRE(table != nullptr);
        REQUIRE(table->getSize() == 20); // all combinations of 5 assignments and 4 variables
        REQUIRE(table->getHeaders().size() == 2);
    }

    SECTION("Works for wildcard") {
        AssignPatternPredicate predicate(*assignSynonym, "_", "unused");
        qm.setFakeAssignsWithPattern({assignStmt1, assignStmt2, assignStmt3, assignStmt4, assignStmt5});
        qm.setAllFakeVariable({variableX, variableY, variableZ, variableW});
        auto table = static_pointer_cast<HeaderTable>(predicate.getTable(qm));
        REQUIRE(table != nullptr);
        REQUIRE(table->getSize() == 5); // all 5 assignments
        REQUIRE(table->getHeaders().size() == 1);
        REQUIRE(table->getHeaders()[0]->getName() == "a");
    }

    SECTION("Works for specific variable") {
        AssignPatternPredicate predicate(*assignSynonym, "x", "unused");    // x exists
        qm.setFakeAssignsWithPattern({assignStmt1, assignStmt2, assignStmt3, assignStmt4, assignStmt5});
        qm.setAllFakeVariable({variableX, variableY, variableZ, variableW});
        auto table = static_pointer_cast<HeaderTable>(predicate.getTable(qm));
        REQUIRE(table != nullptr);
        REQUIRE(table->getSize() == 5); // all 5 assignments, since there's match
        REQUIRE(table->getHeaders().size() == 1);
        REQUIRE(table->getHeaders()[0]->getName() == "a");
    }

    SECTION("Works when no assignments") {
        AssignPatternPredicate predicate(*assignSynonym, "_", "unused");
        qm.setFakeAssignsWithPattern({});
        qm.setAllFakeVariable({variableX, variableY, variableZ, variableW});
        auto table = static_pointer_cast<HeaderTable>(predicate.getTable(qm));
        REQUIRE(table != nullptr);
        REQUIRE(table->getSize() == 0);
        REQUIRE(table->getHeaders().size() == 1);
        REQUIRE(table->getHeaders()[0]->getName() == "a");
    }

    SECTION("Works when no variables") {
        AssignPatternPredicate predicate(*assignSynonym, "_", "unused");
        qm.setFakeAssignsWithPattern({assignStmt1, assignStmt2, assignStmt3, assignStmt4, assignStmt5});
        qm.setAllFakeVariable({});
        auto table = static_pointer_cast<HeaderTable>(predicate.getTable(qm));
        REQUIRE(table != nullptr);
        REQUIRE(table->getSize() == 0);
        REQUIRE(table->getHeaders().size() == 1);
        REQUIRE(table->getHeaders()[0]->getName() == "a");
    }
}



