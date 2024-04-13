#include "catch.hpp"

#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/clause/AffectsPredicate.h"

#include "../fakeEntities/FakeQueryManager.cpp"


TEST_CASE("[AffectsPredicate] Test next table retrieval") {
    // Set up fake data
    QueryEvaluationContext qec;
    shared_ptr<FakeQueryManager> qm = make_shared<FakeQueryManager>();
    qec.setQueryManager(qm);
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<PrintStatement> stmt1 = make_shared<PrintStatement>(1, x, "main");
    shared_ptr<PrintStatement> stmt2 = make_shared<PrintStatement>(2, y, "main");
    shared_ptr<ReadStatement> stmt3 = make_shared<ReadStatement>(3, x, "main");
    shared_ptr<ReadStatement> stmt4 = make_shared<ReadStatement>(4, y, "main");
    shared_ptr<PrintStatement> stmt5 = make_shared<PrintStatement>(5, y, "main");
    qm->addFakeAffects(stmt1, stmt2);
    qm->addFakeAffects(stmt2, stmt3);
    qm->addFakeAffects(stmt3, stmt4);
    qm->addFakeAffects(stmt4, stmt5);

    SECTION("Using statement numbers") {
        // All Failing here

        SECTION("Affects(1, 2) is true") {
            AffectsPredicate affectsPred(1, 2);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Affects(2, 3) is true") {
            AffectsPredicate affectsPred(2, 3);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Affects(3, 4) is true") {
            AffectsPredicate affectsPred(3, 4);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Affects(4, 5) is true") {
            AffectsPredicate affectsPred(4, 5);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Affects(5, 4) is false") {
            AffectsPredicate affectsPred(5, 4);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Affects(4, 3) is false") {
            AffectsPredicate affectsPred(4, 3);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Affects(3, 2) is false") {
            AffectsPredicate affectsPred(3, 2);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Affects(2, 1) is false") {
            AffectsPredicate affectsPred(2, 1);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }
    }

    SECTION("Using synonyms only") {
        SECTION("Using stmt synonym type - gets all") {
            Synonym stmtSyn(EntityType::Stmt, "s1");
            Synonym stmtSyn2(EntityType::Stmt, "s2");
            AffectsPredicate affectsPred(stmtSyn, stmtSyn2);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 4);
        }

            // This onwards all fails

        SECTION("Using Print Print synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Print, "s1");
            Synonym stmtSyn2(EntityType::Print, "s2");
            AffectsPredicate affectsPred(stmtSyn, stmtSyn2);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }

        SECTION("Using Print Read synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Print, "s1");
            Synonym stmtSyn2(EntityType::Read, "s2");
            AffectsPredicate affectsPred(stmtSyn, stmtSyn2);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }

        SECTION("Using Read Read synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Read, "s1");
            Synonym stmtSyn2(EntityType::Read, "s2");
            AffectsPredicate affectsPred(stmtSyn, stmtSyn2);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }

        SECTION("Using Read Print synonym type - gets 1") {
            Synonym stmtSyn(EntityType::Read, "s1");
            Synonym stmtSyn2(EntityType::Print, "s2");
            AffectsPredicate affectsPred(stmtSyn, stmtSyn2);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 1);
        }
    }

    SECTION("Using mix of synonyms and statement numbers") {
        Synonym stmtSyn(EntityType::Stmt, "s1");
        SECTION("Affects(1, s1) -- gets 1") {
            AffectsPredicate affectsPred(1, stmtSyn);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 1);
            REQUIRE(table->getRows()[0].getValues()[0]->getName() == "2");
        }

        SECTION("Affects(s1, 1) -- gets 0") {
            AffectsPredicate affectsPred(stmtSyn, 1);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 0);
        }

        SECTION("Affects(s1, 3) -- gets 1") {
            AffectsPredicate affectsPred(stmtSyn, 3);
            auto table = affectsPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 1);
            REQUIRE(table->getRows()[0].getValues()[0]->getName() == "2");
        }
    }
}