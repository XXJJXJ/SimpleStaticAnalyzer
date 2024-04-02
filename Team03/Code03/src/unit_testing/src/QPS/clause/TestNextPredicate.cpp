#include "catch.hpp"

#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/clause/NextPredicate.h"

#include "../fakeEntities/FakeQueryManager.cpp"


TEST_CASE("Test next table retrieval", "[NextPredicate]") {
    // Set up fake data
    QueryEvaluationContext qec = QueryEvaluationContext();
    shared_ptr<FakeQueryManager> qm = make_shared<FakeQueryManager>();
    qec.setQueryManager(qm);
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<PrintStatement> stmt1 = make_shared<PrintStatement>(1, x, "main");
    shared_ptr<PrintStatement> stmt2 = make_shared<PrintStatement>(2, y, "main");
    shared_ptr<ReadStatement> stmt3 = make_shared<ReadStatement>(3, x, "main");
    shared_ptr<ReadStatement> stmt4 = make_shared<ReadStatement>(4, y, "main");
    shared_ptr<PrintStatement> stmt5 = make_shared<PrintStatement>(5, y, "main");
    qm->addFakeNext(stmt1, stmt2); // print follows print
    qm->addFakeNext(stmt2, stmt3); // print follows read
    qm->addFakeNext(stmt3, stmt4); // read follows read
    qm->addFakeNext(stmt4, stmt5); // read follows read

    SECTION("Using statement numbers") {
        // All Failing here

        SECTION("Next(1, 2) is true") {
            NextPredicate followsPred(1, 2);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Next(2, 3) is true") {
            NextPredicate followsPred(2, 3);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Next(3, 4) is true") {
            NextPredicate followsPred(3, 4);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Next(4, 5) is true") {
            NextPredicate followsPred(4, 5);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Next(5, 4) is false") {
            NextPredicate followsPred(5, 4);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Next(4, 3) is false") {
            NextPredicate followsPred(4, 3);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Next(3, 2) is false") {
            NextPredicate followsPred(3, 2);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Next(2, 1) is false") {
            NextPredicate followsPred(2, 1);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }
    }

    SECTION("Using synonyms only") {
        SECTION("Using stmt synonym type - gets all") {
            Synonym stmtSyn(EntityType::Stmt, "s1");
            Synonym stmtSyn2(EntityType::Stmt, "s2");
            NextPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 4);
        }

            // This onwards all fails

        SECTION("Using Print Print synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Print, "s1");
            Synonym stmtSyn2(EntityType::Print, "s2");
            NextPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }

        SECTION("Using Print Read synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Print, "s1");
            Synonym stmtSyn2(EntityType::Read, "s2");
            NextPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }

        SECTION("Using Read Read synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Read, "s1");
            Synonym stmtSyn2(EntityType::Read, "s2");
            NextPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }

        SECTION("Using Read Print synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Read, "s1");
            Synonym stmtSyn2(EntityType::Print, "s2");
            NextPredicate followsPred(stmtSyn, stmtSyn2);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }
    }

    SECTION("Using mix of synonyms and statement numbers") {
        Synonym stmtSyn(EntityType::Stmt, "s1");
        SECTION("Next(1, s1) -- gets 1") {
            NextPredicate followsPred(1, stmtSyn);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 1);
            REQUIRE(table->getRows()[0].getValues()[0]->getName() == "2");
        }

        SECTION("Next(s1, 1) -- gets 0") {
            NextPredicate followsPred(stmtSyn, 1);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 0);
        }

        SECTION("Next(s1, 3) -- gets 1") {
            NextPredicate followsPred(stmtSyn, 3);
            auto table = followsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 1);
            REQUIRE(table->getRows()[0].getValues()[0]->getName() == "2");
        }
    }
}