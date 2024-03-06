#include "catch.hpp"

#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/clause/ParentPredicate.h"

#include "../fakeEntities/FakeQueryManager.cpp"


TEST_CASE("Test parent table retrieval", "[ParentPredicate]") {
    // Set up fake data
    FakeQueryManager qm;
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<PrintStatement> stmt1 = make_shared<PrintStatement>(1, x, "main");
    shared_ptr<PrintStatement> stmt2 = make_shared<PrintStatement>(2, y, "main");
    shared_ptr<ReadStatement> stmt3 = make_shared<ReadStatement>(3, x, "main");
    shared_ptr<ReadStatement> stmt4 = make_shared<ReadStatement>(4, y, "main");
    shared_ptr<PrintStatement> stmt5 = make_shared<PrintStatement>(5, y, "main");
    qm.addFakeParent(stmt1, stmt2); // print follows print
    qm.addFakeParent(stmt2, stmt3); // print follows read
    qm.addFakeParent(stmt3, stmt4); // read follows read
    qm.addFakeParent(stmt4, stmt5); // read follows read

    SECTION("Using statement numbers") {
        // All Failing here

        SECTION("Parent(1, 2) is true") {
            ParentPredicate followsPred(1, 2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Parent(2, 3) is true") {
            ParentPredicate followsPred(2, 3);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Parent(3, 4) is true") {
            ParentPredicate followsPred(3, 4);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Parent(4, 5) is true") {
            ParentPredicate followsPred(4, 5);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Parent(5, 4) is false") {
            ParentPredicate followsPred(5, 4);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Parent(4, 3) is false") {
            ParentPredicate followsPred(4, 3);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Parent(3, 2) is false") {
            ParentPredicate followsPred(3, 2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Parent(2, 1) is false") {
            ParentPredicate followsPred(2, 1);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }
    }

    SECTION("Using synonyms only") {
        SECTION("Using stmt synonym type - gets all") {
            Synonym stmtSyn(EntityType::Stmt, "s1");
            Synonym stmtSyn2(EntityType::Stmt, "s2");
            ParentPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 4);
        }

            // This onwards all fails

        SECTION("Using Print Print synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Print, "s1");
            Synonym stmtSyn2(EntityType::Print, "s2");
            ParentPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }

        SECTION("Using Print Read synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Print, "s1");
            Synonym stmtSyn2(EntityType::Read, "s2");
            ParentPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }

        SECTION("Using Read Read synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Read, "s1");
            Synonym stmtSyn2(EntityType::Read, "s2");
            ParentPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }

        SECTION("Using Read Print synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Read, "s1");
            Synonym stmtSyn2(EntityType::Print, "s2");
            ParentPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }
    }

    SECTION("Using mix of synonyms and statement numbers") {
        Synonym stmtSyn(EntityType::Stmt, "s1");
        SECTION("Parent(1, s1) -- gets 1") {
            ParentPredicate followsPred(1, stmtSyn);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 1);
            REQUIRE(table->getRows()[0].getValues()[0]->getName() == "2");
        }

        SECTION("Parent(s1, 1) -- gets 0") {
            ParentPredicate followsPred(stmtSyn, 1);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 0);
        }

        SECTION("Parent(s1, 3) -- gets 1") {
            ParentPredicate followsPred(stmtSyn, 3);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 1);
            REQUIRE(table->getRows()[0].getValues()[0]->getName() == "2");
        }
    }
}