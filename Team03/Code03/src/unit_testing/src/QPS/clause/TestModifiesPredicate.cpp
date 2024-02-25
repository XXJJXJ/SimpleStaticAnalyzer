#include "catch.hpp"

#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/clause/ModifiesPredicate.h"
#include "qps/entity/evaluation/HeaderTable.h"
#include "../fakeEntities/FakeQueryManager.cpp"


TEST_CASE("Test table retrieval 3", "[ModifiesPredicate]") {
    // Set up fake data
    FakeQueryManager qm;
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<AssignStatement> stmt1 = make_shared<AssignStatement>(1, x, "main");
    shared_ptr<ReadStatement> stmt2 = make_shared<ReadStatement>(2, y, "main");
    qm.addFakeModifies(stmt1, x); // assign modifies x
    qm.addFakeModifies(stmt2, y); // read uses y

    SECTION("Using statement numbers") {
        SECTION("Modifies(1, \"x\") is true") {
            ModifiesPredicate modifiesPred(1, "x");
            auto table = modifiesPred.getTable(qm);
            REQUIRE(table->isBoolean()); // True
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Modifies(2, \"y\") is true") {
            ModifiesPredicate modifiesPred(2, "y");
            auto table = modifiesPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }

        SECTION("Modifies(1, \"y\") is false") {
            ModifiesPredicate modifiesPred(1, "y");
            auto table = modifiesPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }

        SECTION("Modifies(2, \"x\") is false") {
            ModifiesPredicate modifiesPred(2, "x");
            auto table = modifiesPred.getTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }
    }

    SECTION("Using synonyms only - Modifies(s1, v) get 2 rows") {
        Synonym stmtSyn(EntityType::Stmt, "s1");
        Synonym varSyn(EntityType::Variable, "v");
        ModifiesPredicate modifiesPred(stmtSyn, varSyn);
        auto table = modifiesPred.getTable(qm);
        auto headerTable = dynamic_pointer_cast<HeaderTable>(table);
        REQUIRE(headerTable->getRows().size() == 2);
    }
    SECTION("Using pure wildcards") {
        SECTION("Modifies(_, _) - get true") {
            ModifiesPredicate modifiesPred("_", "_");
            auto table = modifiesPred.getTable(qm);
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->isTrue());
        }
        SECTION("Modifies(_, _) - with empty table get false") {
            FakeQueryManager qm2; // empty qm
            ModifiesPredicate modifiesPred("_", "_");
            auto table = modifiesPred.getTable(qm2);
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(!boolTable->isTrue());
        }
    }
    SECTION("Using partial wildcards") {
        SECTION("Modifies(s1, _) - get 2 rows") {
            Synonym stmtSyn(EntityType::Stmt, "s1");
            ModifiesPredicate modifiesPred(stmtSyn, "_");
            auto table = modifiesPred.getTable(qm);
            auto headerTable = dynamic_pointer_cast<HeaderTable>(table);
            REQUIRE(headerTable->getRows().size() == 2);
        }
        SECTION("Modifies(_, v) - get 2 rows") {
            Synonym varSyn(EntityType::Variable, "v1");
            ModifiesPredicate modifiesPred("_", varSyn);
            auto table = modifiesPred.getTable(qm);
            auto headerTable = dynamic_pointer_cast<HeaderTable>(table);
            REQUIRE(headerTable->getRows().size() == 2);
        }
    }
}