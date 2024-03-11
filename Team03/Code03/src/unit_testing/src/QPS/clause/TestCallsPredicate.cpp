#include "catch.hpp"

#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/clause/CallsPredicate.h"

#include "../fakeEntities/FakeQueryManager.cpp"


TEST_CASE("Test table retrieval for Calls") {
    // Set up fake data
    FakeQueryManager qm;
    /*
    Context:
                     first                fifth
                    /     \               /
                second    fourth       sixth
                     \    /            /
                     third   -----  seventh
    */
    shared_ptr<Procedure> first = make_shared<Procedure>("first");
    shared_ptr<Procedure> second = make_shared<Procedure>("second");
    shared_ptr<Procedure> third = make_shared<Procedure>("third");
    shared_ptr<Procedure> fourth = make_shared<Procedure>("fourth");
    shared_ptr<Procedure> fifth = make_shared<Procedure>("fifth");
    shared_ptr<Procedure> sixth = make_shared<Procedure>("sixth");
    shared_ptr<Procedure> seventh = make_shared<Procedure>("seventh");
    qm.addFakeCalls(first, second);
    qm.addFakeCalls(first, fourth);
    qm.addFakeCalls(fourth, third);
    qm.addFakeCalls(second, third);
    qm.addFakeCalls(fifth, sixth);
    qm.addFakeCalls(sixth, seventh);
    qm.addFakeCalls(third, seventh);

    SECTION("Using synonyms only") {
        SECTION("Using procedure synonym type - gets all") {
            Synonym procSyn(EntityType::Procedure, "s1");
            Synonym procSyn2(EntityType::Procedure, "s2");
            CallsPredicate callsPred(procSyn, procSyn2);
            auto table = callsPred.getResultTable(qm);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 7);
        }
    }

    SECTION("Using mix of synonyms and procedure names") {
        Synonym procSyn(EntityType::Procedure, "p");
        SECTION("Calls(\"first\", p) -- gets 2") {
            CallsPredicate callsPred("first", procSyn);
            auto table = callsPred.getResultTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 2);
        }

        SECTION("Calls(p, \"first\") -- gets 0") {
            CallsPredicate callsPred(procSyn, "first");
            auto table = callsPred.getResultTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 0);
        }

        SECTION("Calls(p, \"second\") -- gets 1") {
            CallsPredicate callsPred(procSyn, "second");
            auto table = callsPred.getResultTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 1);
            REQUIRE(table->getRows()[0].getValues()[0]->getName() == "first");
        }

        SECTION("Calls(p, \"third\") -- gets 2") {
            CallsPredicate callsPred(procSyn, "third");
            auto table = callsPred.getResultTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 2);
        }
    }

    SECTION("Using partial wildcards") {
        Synonym procSyn(EntityType::Procedure, "p");
        SECTION("Calls(_, p) -- gets 5") {
            CallsPredicate callsPred("_", procSyn);
            auto table = callsPred.getResultTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getSize() == 5);
        }

        SECTION("Calls(p, _) -- gets 6") {
            CallsPredicate callsPred(procSyn, "_");
            auto table = callsPred.getResultTable(qm);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getSize() == 6);
        }
    }
    SECTION("Using pure wildcards") {
        SECTION("Calls*(_, _) -- gets true") {
            CallsPredicate callsPred("_", "_");
            auto table = callsPred.getResultTable(qm);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->getValue());
        }
    }
}