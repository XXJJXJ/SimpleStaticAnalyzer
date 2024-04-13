#include "catch.hpp"

#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/clause/CallsTPredicate.h"

#include "../fakeEntities/FakeQueryManager.cpp"

TEST_CASE("Test table retrieval for Calls*") {
    // Set up fake data
    QueryEvaluationContext qec;
    shared_ptr<FakeQueryManager> qm = make_shared<FakeQueryManager>();
    qec.setQueryManager(qm);
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
    // direct
    qm->addFakeCallsT(first, second);
    qm->addFakeCallsT(first, fourth);
    qm->addFakeCallsT(first, third);
    qm->addFakeCallsT(first, seventh);
    qm->addFakeCallsT(fourth, third);
    qm->addFakeCallsT(fourth, seventh);
    qm->addFakeCallsT(second, third);
    qm->addFakeCallsT(second, seventh);
    qm->addFakeCallsT(third, seventh);
    qm->addFakeCallsT(fifth, sixth);
    qm->addFakeCallsT(fifth, seventh);
    qm->addFakeCallsT(sixth, seventh);


    SECTION("Using synonyms only") {
        SECTION("Using procedure synonym type - gets all") {
            Synonym procSyn(EntityType::Procedure, "s1");
            Synonym procSyn2(EntityType::Procedure, "s2");
            CallsTPredicate callsTPred(procSyn, procSyn2);
            auto table = callsTPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 2);
            REQUIRE(table->getRows().size() == 12);
        }
    }

    SECTION("Using mix of synonyms and procedure names") {
        Synonym procSyn(EntityType::Procedure, "p");
        SECTION("Calls*(\"first\", p) -- gets 4") {
            CallsTPredicate callsTPred("first", procSyn);
            auto table = callsTPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 4);
        }

        SECTION("Calls*(p, \"fifth\") -- gets 0") {
            CallsTPredicate callsTPred(procSyn, "fifth");
            auto table = callsTPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 0);
        }

        SECTION("Calls*(p, \"second\") -- gets 1") {
            CallsTPredicate callsTPred(procSyn, "second");
            auto table = callsTPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 1);
            REQUIRE(table->getRows()[0].getValues()[0]->getName() == "first");
        }

        SECTION("Calls*(p, \"third\") -- gets 3") {
            CallsTPredicate callsTPred(procSyn, "third");
            auto table = callsTPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getRows().size() == 3);
        }
    }SECTION("Using partial wildcards") {
        Synonym procSyn(EntityType::Procedure, "p");
        SECTION("Calls*(_, p) -- gets 5") {
            CallsTPredicate callsTPred("_", procSyn);
            auto table = callsTPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getSize() == 5);
        }

        SECTION("Calls*(p, _) -- gets 6") {
            CallsTPredicate callsTPred(procSyn, "_");
            auto table = callsTPred.getResultTable(qec);
            REQUIRE(table->getColumnCount() == 1);
            REQUIRE(table->getSize() == 6);
        }
    }SECTION("Using pure wildcards") {
        SECTION("Calls*(_, _) -- gets true") {
            CallsTPredicate callsTPred("_", "_");
            auto table = callsTPred.getResultTable(qec);
            REQUIRE(table->isBoolean());
            auto boolTable = dynamic_pointer_cast<BooleanTable>(table);
            REQUIRE(boolTable->getValue());
        }
    }
}