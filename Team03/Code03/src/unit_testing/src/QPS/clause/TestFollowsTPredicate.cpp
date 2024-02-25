#include <catch.hpp>

#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/clause/FollowsTPredicate.h"

#include "../fakeEntities/FakeQueryManager.cpp"

FakeQueryManager qm;

TEST_CASE("Test FollowsTPredicate with statement numbers", "[FollowsTPredicate]") {
    // Initializing all data
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<PrintStatement> stmt1 = make_shared<PrintStatement>(1, x, "main");
    shared_ptr<PrintStatement> stmt2 = make_shared<PrintStatement>(2, y, "main");
    shared_ptr<ReadStatement> stmt3 = make_shared<ReadStatement>(3, x, "main");
    shared_ptr<ReadStatement> stmt4 = make_shared<ReadStatement>(4, y, "main");
    shared_ptr<PrintStatement> stmt5 = make_shared<PrintStatement>(5, y, "main");

    // Adding all FollowsT statements
    qm.addFakeFollowsT(stmt1, stmt2); // print follows print
    qm.addFakeFollowsT(stmt1, stmt3);
    qm.addFakeFollowsT(stmt1, stmt4);
    qm.addFakeFollowsT(stmt1, stmt5);

    qm.addFakeFollowsT(stmt2, stmt3); // print follows read
    qm.addFakeFollowsT(stmt2, stmt4);
    qm.addFakeFollowsT(stmt2, stmt5);

    qm.addFakeFollowsT(stmt3, stmt4); // read follows read
    qm.addFakeFollowsT(stmt3, stmt5);

    qm.addFakeFollowsT(stmt4, stmt5); // read follows read

    SECTION("Using synonyms only") {
        SECTION("Follows(1, 2) is true") {
            FollowsTPredicate followsTPred(1, 2);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Follows(1, 3) is true") {
            FollowsTPredicate followsTPred(1, 3);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Follows(1, 4) is true") {
            FollowsTPredicate followsTPred(1, 4);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Follows(1, 5) is true") {
            FollowsTPredicate followsTPred(1, 5);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Follows(2, 3) is true") {
            FollowsTPredicate followsTPred(2, 3);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Follows(2, 4) is true") {
            FollowsTPredicate followsTPred(2, 4);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Follows(2, 5) is true") {
            FollowsTPredicate followsTPred(2, 5);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Follows(3, 4) is true") {
            FollowsTPredicate followsTPred(3, 4);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Follows(3, 5) is true") {
            FollowsTPredicate followsTPred(3, 5);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Follows(4, 5) is true") {
            FollowsTPredicate followsTPred(4, 5);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Follows(5, 4) is false") {
            FollowsTPredicate followsTPred(5, 4);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Follows(4, 3) is false") {
            FollowsTPredicate followsTPred(4, 3);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Follows(5, 3) is false") {
            FollowsTPredicate followsTPred(5, 3);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Follows(3, 2) is false") {
            FollowsTPredicate followsTPred(3, 2);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Follows(4, 2) is false") {
            FollowsTPredicate followsTPred(4, 2);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Follows(5, 2) is false") {
            FollowsTPredicate followsTPred(5, 2);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Follows(2, 1) is false") {
            FollowsTPredicate followsTPred(2, 1);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Follows(3, 1) is false") {
            FollowsTPredicate followsTPred(3, 1);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Follows(4, 1) is false") {
            FollowsTPredicate followsTPred(4, 1);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Follows(5, 1) is false") {
            FollowsTPredicate followsTPred(5, 1);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }
    }

    SECTION("Using mix of synonyms and statement numbers") {
        Synonym stmtSyn(EntityType::Stmt, "s1");
        SECTION("Follows(1, s1) -- gets 1") {
            FollowsTPredicate followsTPred(1, stmtSyn);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 1);
            REQUIRE(table->getRows()[0].getValues()[0]->getName() == "2");
        }

        SECTION("Follows(s1, 1) -- gets 0") {
            FollowsTPredicate followsTPred(stmtSyn, 1);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 0);
        }

        SECTION("Follows(s1, 3) -- gets 1") {
            FollowsTPredicate followsTPred(stmtSyn, 3);
            auto table = followsTPred.getTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 1);
            REQUIRE(table->getRows()[0].getValues()[0]->getName() == "2");
        }
    }
}