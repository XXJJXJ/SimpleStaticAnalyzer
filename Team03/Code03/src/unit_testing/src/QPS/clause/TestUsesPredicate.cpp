#include "catch.hpp"

#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/clause/UsesPredicate.h"
#include "qps/entity/evaluation/HeaderTable.h"
#include "../fakeEntities/FakeQueryManager.cpp"


TEST_CASE("Test table retrieval 2", "[UsesPredicate]") {
    // Set up fake data
    FakeQueryManager qm;
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<AssignStatement> stmt1 = make_shared<AssignStatement>(1, x, "main");
    shared_ptr<PrintStatement> stmt2 = make_shared<PrintStatement>(2, y, "main");
    qm.addFakeUses(stmt1, x); // assign uses x
    qm.addFakeUses(stmt2, y); // print uses y

    SECTION("Using statement numbers") {
        SECTION("Uses(1, \"x\") is true") {
            UsesPredicate usesPred(1, "x");
            auto table = usesPred.getTable(qm);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Uses(2, \"y\") is true") {
            UsesPredicate usesPred(2, "y");
            auto table = usesPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Uses(1, \"y\") is false") {
            UsesPredicate usesPred(1, "y");
            auto table = usesPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Uses(2, \"x\") is false") {
            UsesPredicate usesPred(2, "x");
            auto table = usesPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }
    }

    SECTION("Using synonyms only - Uses(s1, v) get 2 rows") {
        Synonym stmtSyn(EntityType::Stmt, "s1");
        Synonym varSyn(EntityType::Variable, "v");
        UsesPredicate usesPred(stmtSyn, varSyn);
        auto table = usesPred.getTable(qm);
        auto headerTable = dynamic_pointer_cast<HeaderTable>(table);
        REQUIRE(headerTable->getRows().size() == 2);
    }
    SECTION("Using pure wildcards") {
        SECTION("Uses(_, _) - get true") {
            UsesPredicate usesPred("_", "_");
            auto table = usesPred.getTable(qm);
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Uses(_, _) - with empty table get false") {
            FakeQueryManager qm2; // empty qm
            UsesPredicate usesPred("_", "_");
            auto table = usesPred.getTable(qm2);
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }
    }
    SECTION("Using partial wildcards") {
        SECTION("Uses(s1, _) - get 2 rows") {
            Synonym stmtSyn(EntityType::Stmt, "s1");
            UsesPredicate usesPred(stmtSyn, "_");
            auto table = usesPred.getTable(qm);
            auto headerTable = dynamic_pointer_cast<HeaderTable>(table);
            REQUIRE(headerTable->getRows().size() == 2);
        }
        SECTION("Uses(_, v) - get 2 rows") {
            Synonym varSyn(EntityType::Variable, "v1");
            UsesPredicate usesPred("_", varSyn);
            auto table = usesPred.getTable(qm);
            auto headerTable = dynamic_pointer_cast<HeaderTable>(table);
            REQUIRE(headerTable->getRows().size() == 2);
        }
    }
}