#include "catch.hpp"

#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/clause/FollowsPredicate.h"

#include "../fakeEntities/FakeQueryManager.cpp"


TEST_CASE("Test table retrieval", "[FollowsPredicate]") {
    // Set up fake data
    FakeQueryManager qm;
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<PrintStatement> stmt1 = make_shared<PrintStatement>(1, x, "main");
    shared_ptr<PrintStatement> stmt2 = make_shared<PrintStatement>(2, y, "main");
    shared_ptr<ReadStatement> stmt3 = make_shared<ReadStatement>(3, x, "main");
    shared_ptr<ReadStatement> stmt4 = make_shared<ReadStatement>(4, y, "main");
    shared_ptr<PrintStatement> stmt5 = make_shared<PrintStatement>(5, y, "main");
    qm.addFakeFollows(stmt1, stmt2); // print follows print
    qm.addFakeFollows(stmt2, stmt3); // print follows read
    qm.addFakeFollows(stmt3, stmt4); // read follows read
    qm.addFakeFollows(stmt4, stmt5); // read follows read

    SECTION("Using statement numbers") {
        // All Failing here

        SECTION("Follows(1, 2) is true") {
            FollowsPredicate followsPred(1, 2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Follows(2, 3) is true") {
            FollowsPredicate followsPred(2, 3);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Follows(3, 4) is true") {
            FollowsPredicate followsPred(3, 4);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Follows(4, 5) is true") {
            FollowsPredicate followsPred(4, 5);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

         SECTION("Follows(5, 4) is false") {
             FollowsPredicate followsPred(5, 4);
             auto table = followsPred.getTable(qm);
             REQUIRE(table->isBoolean());
             auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
             REQUIRE(!boolTable->isTrue());
         }

         SECTION("Follows(4, 3) is false") {
             FollowsPredicate followsPred(4, 3);
             auto table = followsPred.getTable(qm);
             REQUIRE(table->isBoolean());
             auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
             REQUIRE(!boolTable->isTrue());
         }

         SECTION("Follows(3, 2) is false") {
             FollowsPredicate followsPred(3, 2);
             auto table = followsPred.getTable(qm);
             REQUIRE(table->isBoolean());
             auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
             REQUIRE(!boolTable->isTrue());
         }

         SECTION("Follows(2, 1) is false") {
             FollowsPredicate followsPred(2, 1);
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
            FollowsPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 4);
        }

        // This onwards all fails

        SECTION("Using Print Print synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Print, "s1");
            Synonym stmtSyn2(EntityType::Print, "s2");
            FollowsPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }

        SECTION("Using Print Read synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Print, "s1");
            Synonym stmtSyn2(EntityType::Read, "s2");
            FollowsPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }

        SECTION("Using Read Read synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Read, "s1");
            Synonym stmtSyn2(EntityType::Read, "s2");
            FollowsPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }

        SECTION("Using Read Print synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Read, "s1");
            Synonym stmtSyn2(EntityType::Print, "s2");
            FollowsPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }
    }

    SECTION("Using mix of synonyms and statement numbers") {
        Synonym stmtSyn(EntityType::Stmt, "s1");
        SECTION("Follows(1, s1) -- gets 1") {
            FollowsPredicate followsPred(1, stmtSyn);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 1);
            REQUIRE(table->getRows()[0].getValues()[0]->getName() == "2");
        }

        SECTION("Follows(s1, 1) -- gets 0") {
            FollowsPredicate followsPred(stmtSyn, 1);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 0);
        }

        SECTION("Follows(s1, 3) -- gets 1") {
            FollowsPredicate followsPred(stmtSyn, 3);
            auto table = followsPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 1);
            REQUIRE(table->getRows()[0].getValues()[0]->getName() == "2");
        }
    }
}