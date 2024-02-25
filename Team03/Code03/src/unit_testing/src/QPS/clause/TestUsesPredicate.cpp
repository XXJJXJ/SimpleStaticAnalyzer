#include "catch.hpp"

#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/clause/UsesPredicate.h"

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

    SECTION("Using synonyms only") {
        
    }
}