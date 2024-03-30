#include "catch.hpp"

#include "common/Constant.h"
#include "common/Variable.h"
#include "common/Procedure.h"
#include "common/Statement.h"
#include "pkb/PopulatePKB.h"
#include "pkb/QueryPKB.h"

using namespace std;


TEST_CASE("Store and retrieve FollowS and FollowT") {
    Populator pop;
    pop.clear();

    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<PrintStatement> stmt1 = make_shared<PrintStatement>(1, x, "main");
    shared_ptr<PrintStatement> stmt2 = make_shared<PrintStatement>(2, y, "main");
    shared_ptr<ReadStatement> stmt3 = make_shared<ReadStatement>(3, x, "main");
    shared_ptr<ReadStatement> stmt4 = make_shared<ReadStatement>(4, y, "main");
    // Sections are unlinked, don't anyhow use
    REQUIRE(pop.addFollow(stmt1, stmt2));
    REQUIRE(pop.addFollow(stmt2, stmt3));
    REQUIRE(pop.addFollow(stmt3, stmt4));

    REQUIRE(!pop.addFollow(stmt1, stmt3));
    REQUIRE(!pop.addFollow(stmt1, stmt4));

    REQUIRE(!pop.addFollow(stmt2, stmt1));
    REQUIRE(!pop.addFollow(stmt2, stmt4));

    REQUIRE(!pop.addFollow(stmt3, stmt1));
    REQUIRE(!pop.addFollow(stmt3, stmt2));

    REQUIRE(!pop.addFollow(stmt4, stmt2));
    REQUIRE(!pop.addFollow(stmt4, stmt1));
    REQUIRE(!pop.addFollow(stmt4, stmt3));


    QueryManager qm;
    auto followS = qm.getFollowSMap();
    REQUIRE((followS[stmt1].find(stmt2) != followS[stmt1].end()));
    REQUIRE((followS[stmt2].find(stmt3) != followS[stmt2].end()));
    REQUIRE((followS[stmt3].find(stmt4) != followS[stmt3].end()));

    auto followT = qm.getFollowTMap();
    REQUIRE((followT[stmt1].find(stmt2) != followT[stmt1].end()));
    REQUIRE((followT[stmt1].find(stmt3) != followT[stmt1].end()));
    REQUIRE((followT[stmt1].find(stmt4) != followT[stmt1].end()));

    REQUIRE((followT[stmt2].find(stmt3) != followT[stmt2].end()));
    REQUIRE((followT[stmt2].find(stmt4) != followT[stmt2].end()));

    REQUIRE((followT[stmt3].find(stmt4) != followT[stmt3].end()));
    pop.clear();
}

TEST_CASE("Store and retrieve ParentS and ParentT") {
    Populator pop;
    pop.clear();

    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<ConditionalOperation> cond = make_shared<ConditionalOperation>("test_expression", make_pair<>(x, y));
    shared_ptr<WhileStatement> stmt1 = make_shared<WhileStatement>(1, cond, "main");
    shared_ptr<IfStatement> stmt2 = make_shared<IfStatement>(2, cond,"main");
    // then
    shared_ptr<PrintStatement> stmt3 = make_shared<PrintStatement>(3, y, "main");
    shared_ptr<ReadStatement> stmt4 = make_shared<ReadStatement>(4, x, "main");
    // else
    shared_ptr<PrintStatement> stmt5 = make_shared<PrintStatement>(5, y, "main");
    shared_ptr<ReadStatement> stmt6 = make_shared<ReadStatement>(6, x, "main");

    // Positive cases
    REQUIRE(pop.addParent(stmt1, stmt2));
    REQUIRE(pop.addParent(stmt2, stmt3));
    REQUIRE(pop.addParent(stmt2, stmt4));
    REQUIRE(pop.addParent(stmt2, stmt5));
    REQUIRE(pop.addParent(stmt2, stmt6));

    // Negative cases
    REQUIRE(!pop.addParent(stmt2, stmt1));
    REQUIRE(!pop.addParent(stmt3, stmt1));
    // This takes cares of other combinations
    REQUIRE(!pop.addParent(stmt3, stmt2));
    REQUIRE(!pop.addParent(stmt3, stmt3));
    REQUIRE(!pop.addParent(stmt3, stmt4));
    REQUIRE(!pop.addParent(stmt3, stmt5));

    // Retrieval
    QueryManager qm;
    auto parentS = qm.getParentSMap();
    REQUIRE((parentS[stmt1].find(stmt2) != parentS[stmt1].end()));
    REQUIRE((parentS[stmt1].find(stmt3) == parentS[stmt1].end()));
    REQUIRE((parentS[stmt1].find(stmt4) == parentS[stmt1].end()));
    REQUIRE((parentS[stmt1].find(stmt5) == parentS[stmt1].end()));
    REQUIRE((parentS[stmt1].find(stmt6) == parentS[stmt1].end()));

    REQUIRE((parentS[stmt2].find(stmt1) == parentS[stmt2].end()));
    REQUIRE((parentS[stmt2].find(stmt3) != parentS[stmt2].end()));
    REQUIRE((parentS[stmt2].find(stmt4) != parentS[stmt2].end()));
    REQUIRE((parentS[stmt2].find(stmt5) != parentS[stmt2].end()));
    REQUIRE((parentS[stmt2].find(stmt6) != parentS[stmt2].end()));

    auto parentT = qm.getParentTMap();
    REQUIRE((parentT[stmt1].find(stmt2) != parentT[stmt1].end()));
    REQUIRE((parentT[stmt1].find(stmt3) != parentT[stmt1].end()));
    REQUIRE((parentT[stmt1].find(stmt4) != parentT[stmt1].end()));
    REQUIRE((parentT[stmt1].find(stmt5) != parentT[stmt1].end()));
    REQUIRE((parentT[stmt1].find(stmt6) != parentT[stmt1].end()));

    REQUIRE((parentT[stmt2].find(stmt1) == parentT[stmt2].end()));
    REQUIRE((parentT[stmt2].find(stmt2) == parentT[stmt2].end()));
    REQUIRE((parentT[stmt2].find(stmt3) != parentT[stmt2].end()));
    REQUIRE((parentT[stmt2].find(stmt4) != parentT[stmt2].end()));
    REQUIRE((parentT[stmt2].find(stmt5) != parentT[stmt2].end()));
    REQUIRE((parentT[stmt2].find(stmt6) != parentT[stmt2].end()));
    pop.clear();
}

TEST_CASE("Store and retrieve Modifies") {
    Populator pop;
    pop.clear();
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<ReadStatement> stmt4 = make_shared<ReadStatement>(4, x, "main");
    pop.addModifies(stmt4, x);

    QueryManager qm;
    auto modifiesAllStmt = qm.getModifyAllMap();
    REQUIRE((modifiesAllStmt[stmt4].find(y) == modifiesAllStmt[stmt4].end()));
    REQUIRE((modifiesAllStmt[stmt4].find(x) != modifiesAllStmt[stmt4].end()));

    auto modifiesAllRead = qm.getModifyByReadMap();
    REQUIRE((modifiesAllRead[stmt4].find(y) == modifiesAllRead[stmt4].end()));
    REQUIRE((modifiesAllRead[stmt4].find(x) != modifiesAllRead[stmt4].end()));

    auto modifiesByProcedure = qm.getModifyByProcedureMap();
    REQUIRE((modifiesByProcedure["main"].find(y) == modifiesByProcedure["main"].end()));
    REQUIRE((modifiesByProcedure["main"].find(x) != modifiesByProcedure["main"].end()));
    pop.clear();
}

TEST_CASE("Store and retrieve Uses") {
    Populator pop;
    pop.clear();
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<PrintStatement> stmt3 = make_shared<PrintStatement>(3, y, "main");
    pop.addUses(stmt3, y);

    QueryManager qm;
    auto useAllStmt = qm.getUseAllMap();
    REQUIRE((useAllStmt[stmt3].find(y) != useAllStmt[stmt3].end()));
    REQUIRE((useAllStmt[stmt3].find(x) == useAllStmt[stmt3].end()));

    auto useAllPrint = qm.getUseByPrintMap();
    REQUIRE((useAllPrint[stmt3].find(y) != useAllPrint[stmt3].end()));
    REQUIRE((useAllPrint[stmt3].find(x) == useAllPrint[stmt3].end()));

    auto useByProcedure = qm.getUseByProcedureMap();
    REQUIRE((useByProcedure["main"].find(y) != useByProcedure["main"].end()));
    REQUIRE((useByProcedure["main"].find(x) == useByProcedure["main"].end()));
    pop.clear();
}

TEST_CASE("Test container stmt Uses and Modifies") {
    Populator pop;
    pop.clear();

    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<ConditionalOperation> cond = make_shared<ConditionalOperation>("test_expression", make_pair<>(x, y));
    shared_ptr<WhileStatement> stmt1 = make_shared<WhileStatement>(1, cond, "main");
    shared_ptr<IfStatement> stmt2 = make_shared<IfStatement>(2, cond,"main");
    // then
    shared_ptr<PrintStatement> stmt3 = make_shared<PrintStatement>(3, y, "main");
    shared_ptr<ReadStatement> stmt4 = make_shared<ReadStatement>(4, x, "main");
    // else
    shared_ptr<PrintStatement> stmt5 = make_shared<PrintStatement>(5, x, "main");
    shared_ptr<ReadStatement> stmt6 = make_shared<ReadStatement>(6, y, "main");
    // Random while loop in outermost layer and has nothing inside (not allowed, but used for the sake of negative testcases)
    shared_ptr<WhileStatement> stmt7 = make_shared<WhileStatement>(7, cond, "main");


    pop.addParent(stmt1, stmt2);
    pop.addParent(stmt2, stmt3);
    pop.addParent(stmt2, stmt4);
    pop.addParent(stmt2, stmt5);
    pop.addParent(stmt2, stmt6);

    pop.addUses(stmt3, y);
    pop.addUses(stmt5, x);

    pop.addModifies(stmt4, x);
    pop.addModifies(stmt6, y);

    pop.tabulate();

    QueryManager qm;
    SECTION("Test stmt container uses") {
        auto useAllStmt = qm.getUseAllMap();

        SECTION("Trivial test cases, direct uses, either x or y") {
            REQUIRE((useAllStmt[stmt3].find(y) != useAllStmt[stmt3].end()));
            REQUIRE((useAllStmt[stmt3].find(x) == useAllStmt[stmt3].end()));

            REQUIRE((useAllStmt[stmt5].find(x) != useAllStmt[stmt5].end()));
            REQUIRE((useAllStmt[stmt5].find(y) == useAllStmt[stmt5].end()));
        }
        
        // if statement have both
        SECTION("Parent if statement uses both x and y") {
            REQUIRE((useAllStmt[stmt2].find(x) != useAllStmt[stmt2].end()));
            REQUIRE((useAllStmt[stmt2].find(y) != useAllStmt[stmt2].end()));
        }
        
        SECTION("Parent while statement uses both x and y") {
            REQUIRE((useAllStmt[stmt1].find(x) != useAllStmt[stmt1].end()));
            REQUIRE((useAllStmt[stmt1].find(y) != useAllStmt[stmt1].end()));
        }

        SECTION("Dummy while statement with nothing") {
            REQUIRE((useAllStmt[stmt7].find(x) == useAllStmt[stmt7].end()));
            REQUIRE((useAllStmt[stmt7].find(y) == useAllStmt[stmt7].end()));
        }
    }
    
    SECTION("Test stmt container modifies") {
        auto modifiesAllStmt = qm.getModifyAllMap();

        SECTION("Trivial test cases, direct modifies, either x or y") {
            REQUIRE((modifiesAllStmt[stmt4].find(y) == modifiesAllStmt[stmt4].end()));
            REQUIRE((modifiesAllStmt[stmt4].find(x) != modifiesAllStmt[stmt4].end()));

            REQUIRE((modifiesAllStmt[stmt6].find(x) == modifiesAllStmt[stmt6].end()));
            REQUIRE((modifiesAllStmt[stmt6].find(y) != modifiesAllStmt[stmt6].end()));
        }
        
        // if statement have both
        SECTION("Parent if statement modifies both x and y") {
            REQUIRE((modifiesAllStmt[stmt2].find(x) != modifiesAllStmt[stmt2].end()));
            REQUIRE((modifiesAllStmt[stmt2].find(y) != modifiesAllStmt[stmt2].end()));
        }
        
        SECTION("Parent while statement modifies both x and y") {
            REQUIRE((modifiesAllStmt[stmt1].find(x) != modifiesAllStmt[stmt1].end()));
            REQUIRE((modifiesAllStmt[stmt1].find(y) != modifiesAllStmt[stmt1].end()));
        }

        SECTION("Dummy while statement with nothing") {
            REQUIRE((modifiesAllStmt[stmt7].find(x) == modifiesAllStmt[stmt7].end()));
            REQUIRE((modifiesAllStmt[stmt7].find(y) == modifiesAllStmt[stmt7].end()));
        }
    }
    qm.clear();
}

TEST_CASE("Test Uses and Modifies with Call Statement") {
    /* ===== Context ======
    procedure first {
        call second;
    }
    procedure second {
        print x;
        call third;
        call fourth;
    }
    procedure third {
        read y;
    }
    procedure fourth {
        read z;
    }
    */
    Populator pop;
    pop.clear();
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<Variable> z = make_shared<Variable>("z");
    shared_ptr<Procedure> first = make_shared<Procedure>("first");
    shared_ptr<Procedure> second = make_shared<Procedure>("second");
    shared_ptr<CallStatement> stmt1 = make_shared<CallStatement>(1, second, "first");
    shared_ptr<PrintStatement> stmt2 = make_shared<PrintStatement>(2, x, "second");
    shared_ptr<Procedure> third = make_shared<Procedure>("third");
    shared_ptr<Procedure> fourth = make_shared<Procedure>("fourth");
    shared_ptr<CallStatement> stmt3 = make_shared<CallStatement>(3, third, "second");
    shared_ptr<CallStatement> stmt4 = make_shared<CallStatement>(4, fourth, "second");
    shared_ptr<ReadStatement> stmt5 = make_shared<ReadStatement>(5, y, "third");
    shared_ptr<ReadStatement> stmt6 = make_shared<ReadStatement>(6, z, "fourth");

    // Adding to populator
    pop.addProcedure(first);
    pop.addProcedure(second);
    pop.addProcedure(third);
    pop.addProcedure(fourth);
    pop.addUses(stmt2, x);
    pop.addModifies(stmt5, y);
    pop.addModifies(stmt6, z);
    pop.addCallStatement(stmt1);
    pop.addCallStatement(stmt3);
    pop.addCallStatement(stmt4);
    pop.tabulate();

    QueryManager qm;
    /* ==== Expected relations ====
    calls: (x3) {(first, second), (second, third), (second,fourth)}
    calls*: (x5) {
                (first, second), (first, third), (first,fourth)
                (second, third), (second, fourth)
            }
    */
    SECTION("Calls and Calls* test") {
        REQUIRE(qm.getCallS().size() == 3);
        REQUIRE(qm.getCallT().size() == 5);
    }
    /* ==== Expected relations ====
    Uses(c, _): {
        (1, x)
    }
    */
    SECTION("Uses with call statement") {
        auto res = qm.getUseByType(EntityType::Call);
        REQUIRE(res.size() == 1);
        // Only 1, so can compare this way
        REQUIRE(res[0][0]->getName() == "1");
        REQUIRE(res[0][1]->getName() == "x");
    }
    /* ==== Expected relations ====
    Modifies(c, _): {
        (1, y), (1, z)
        (3, y),
        (4, z)
    }
    */
    SECTION("Modifies with call statement") {
        auto res = qm.getModifyByType(EntityType::Call);
        REQUIRE(res.size() == 4);
        unordered_map<string, unordered_set<string>> resMap;
        for (auto & p : res) {
            resMap[p[0]->getName()].insert(p[1]->getName());
        }
        REQUIRE(resMap["1"].size() == 2);
        REQUIRE(resMap["1"].find("y") != resMap["1"].end());
        REQUIRE(resMap["1"].find("z") != resMap["1"].end());
        REQUIRE(resMap["3"].size() == 1);
        REQUIRE(resMap["3"].find("y") != resMap["3"].end());
        REQUIRE(resMap["4"].size() == 1);
        REQUIRE(resMap["4"].find("z") != resMap["4"].end());
    }
    qm.clear();
}

TEST_CASE("Store and retrieve NextS and NextT") {
    Populator pop;
    pop.clear();
    /* ======= Context ========
    procedure main {
    1    x = <something>
    2    while (x < y) {
    3        if (x < y) then {
    4            print y;
    5            read x;
    6        } else { print x;
    7            read y;}}
    8    call test;}
    9    if (x < y) then {
   10       print y;
   11    } else { read x;}
   12    call test2;
    */
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<ConditionalOperation> cond = make_shared<ConditionalOperation>("test_expression", make_pair<>(x, y));
    shared_ptr<AssignStatement> stmt0 = make_shared<AssignStatement>(1, x, "main");
    shared_ptr<WhileStatement> stmt1 = make_shared<WhileStatement>(2, cond, "main");
    shared_ptr<IfStatement> stmt2 = make_shared<IfStatement>(3, cond,"main");
    shared_ptr<PrintStatement> stmt3 = make_shared<PrintStatement>(4, y, "main");
    shared_ptr<ReadStatement> stmt4 = make_shared<ReadStatement>(5, x, "main");
    shared_ptr<PrintStatement> stmt5 = make_shared<PrintStatement>(6, x, "main");
    shared_ptr<ReadStatement> stmt6 = make_shared<ReadStatement>(7, y, "main");
    // Random while loop in outermost layer and has nothing inside (not allowed, but used for the sake of negative testcases)
    shared_ptr<CallStatement> stmt7 = make_shared<CallStatement>(8, make_shared<Procedure>("test"), "main");
    shared_ptr<IfStatement> stmt8 = make_shared<IfStatement>(9, cond, "main");
    shared_ptr<PrintStatement> stmt9 = make_shared<PrintStatement>(10, y, "main");
    shared_ptr<ReadStatement> stmt10 = make_shared<ReadStatement>(11, x, "main");
    shared_ptr<CallStatement> stmt11 = make_shared<CallStatement>(12, make_shared<Procedure>("test2"), "main");
    pop.addNext(stmt0, stmt1);
    pop.addNext(stmt1, stmt2);
    pop.addNext(stmt1, stmt7);
    pop.addNext(stmt2, stmt3);
    pop.addNext(stmt3, stmt4);
    pop.addNext(stmt4, stmt1);
    pop.addNext(stmt2, stmt5);
    pop.addNext(stmt5, stmt6);
    pop.addNext(stmt6, stmt1);
    pop.addNext(stmt7, stmt8);
    pop.addNext(stmt8, stmt9);
    pop.addNext(stmt8, stmt10);
    pop.addNext(stmt9, stmt11);
    pop.addNext(stmt10, stmt11);
    // put statements into while for nextT tabulation
    stmt1->addStatement(stmt2);
    stmt1->addStatement(stmt3);
    stmt1->addStatement(stmt4);
    stmt1->addStatement(stmt5);
    stmt1->addStatement(stmt6);

    QueryManager qm;
    auto nextS = qm.getNextS();
    auto nextT = qm.getNextT();
    SECTION("Check NextS") {
        REQUIRE(nextS.size() == 14);
        unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> directMap;
        for (auto & p : nextS) {
            auto castedStmt1 = dynamic_pointer_cast<Statement>(p[0]);
            auto castedStmt2 = dynamic_pointer_cast<Statement>(p[1]);
            directMap[castedStmt1].insert(castedStmt2);
        }
        // check next(p, _) at most 2 for any p
        for (auto & p : directMap) {
            // size at most 2
            REQUIRE(directMap[p.first].size() <= 2);
        }

        REQUIRE(directMap[stmt0].size() == 1);
        REQUIRE(directMap[stmt0].find(stmt1) != directMap[stmt0].end());

        REQUIRE(directMap[stmt1].size() == 2);
        REQUIRE(directMap[stmt1].find(stmt2) != directMap[stmt1].end());
        REQUIRE(directMap[stmt1].find(stmt7) != directMap[stmt1].end());

        REQUIRE(directMap[stmt2].size() == 2);
        REQUIRE(directMap[stmt2].find(stmt3) != directMap[stmt2].end());
        REQUIRE(directMap[stmt2].find(stmt5) != directMap[stmt2].end());

        REQUIRE(directMap[stmt3].size() == 1);
        REQUIRE(directMap[stmt3].find(stmt4) != directMap[stmt3].end());

        REQUIRE(directMap[stmt4].size() == 1);
        REQUIRE(directMap[stmt4].find(stmt1) != directMap[stmt4].end());

        REQUIRE(directMap[stmt5].size() == 1);
        REQUIRE(directMap[stmt5].find(stmt6) != directMap[stmt5].end());

        REQUIRE(directMap[stmt6].size() == 1);
        REQUIRE(directMap[stmt6].find(stmt1) != directMap[stmt6].end());

        REQUIRE(directMap[stmt7].size() == 1);
        REQUIRE(directMap[stmt7].find(stmt8) != directMap[stmt7].end());
        
        REQUIRE(directMap[stmt8].size() == 2);
        REQUIRE(directMap[stmt8].find(stmt9) != directMap[stmt8].end());
        REQUIRE(directMap[stmt8].find(stmt10) != directMap[stmt8].end());

        REQUIRE(directMap[stmt9].size() == 1);
        REQUIRE(directMap[stmt9].find(stmt11) != directMap[stmt9].end());

        REQUIRE(directMap[stmt10].size() == 1);
        REQUIRE(directMap[stmt10].find(stmt11) != directMap[stmt10].end());

        REQUIRE(directMap[stmt11].size() == 0);
    }

    SECTION("Check NextT") {
        unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> transitiveMap;
        for (auto & p : nextT) {
            auto castedStmt1 = dynamic_pointer_cast<Statement>(p[0]);
            auto castedStmt2 = dynamic_pointer_cast<Statement>(p[1]);
            transitiveMap[castedStmt1].insert(castedStmt2);
        }
        // first statement ever, should be before all statements
        REQUIRE(transitiveMap[stmt0].size() == 11);
        // while statement after first, can reach itself, so still 7
        REQUIRE(transitiveMap[stmt1].size() == 11);
        // statements within while, should be able to reach itself as well as whatever the while loops can reach
        REQUIRE(transitiveMap[stmt2].size() == 11);
        REQUIRE(transitiveMap[stmt3].size() == 11);
        REQUIRE(transitiveMap[stmt4].size() == 11);
        REQUIRE(transitiveMap[stmt5].size() == 11);
        REQUIRE(transitiveMap[stmt6].size() == 11);
        // statement after while loop
        REQUIRE(transitiveMap[stmt7].size() == 4);
        REQUIRE(transitiveMap[stmt8].size() == 3);
        REQUIRE(transitiveMap[stmt9].size() == 1);
        REQUIRE(transitiveMap[stmt10].size() == 1);
        REQUIRE(transitiveMap[stmt11].size() == 0);
    }

    SECTION("Check clear") {
        qm.clear();
        REQUIRE(qm.getNextS().size() == 0);
        REQUIRE(qm.getNextT().size() == 0);
    }
    qm.clear();
}

TEST_CASE("Test calculation of Affects") {
    Populator pop;
    pop.clear();
    /*==== Context
    procedure main {
    1    x = 100;
    2    y = x + 1;
    3    if (y < x) then {
    4        x = 99;
    5        y = y + x;
    6    } else { y = y - 99;}
    7    y = x - 1 + y;
    8    while (y > 1) {
    9        y = y - 1;}}
    ========= Expected outcome ========
    Affects: (1, 2) (1, 7) (2, 5) (2, 6) (4, 5) (4, 7) (5, 7) (6, 7) (7, 9) (9, 9)
    */
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<ConditionalOperation> cond = make_shared<ConditionalOperation>("test_expression", make_pair<>(x, y));
    shared_ptr<AssignStatement> stmt1 = make_shared<AssignStatement>(1, x, "main");
    pop.addModifies(stmt1, x);
    shared_ptr<AssignStatement> stmt2 = make_shared<AssignStatement>(2, y, "main");
    pop.addNext(stmt1, stmt2);
    pop.addModifies(stmt2, y);
    pop.addUses(stmt2, x);
    shared_ptr<IfStatement> stmt3 = make_shared<IfStatement>(3, cond, "main");
    pop.addNext(stmt2, stmt3);
    pop.addUses(stmt3, x);
    pop.addUses(stmt3, y);
    shared_ptr<AssignStatement> stmt4 = make_shared<AssignStatement>(4, x, "main");
    pop.addNext(stmt3, stmt4);
    pop.addParent(stmt3, stmt4);
    pop.addModifies(stmt4, x);
    shared_ptr<AssignStatement> stmt5 = make_shared<AssignStatement>(5, y, "main");
    pop.addNext(stmt4, stmt5);
    pop.addParent(stmt3, stmt5);
    pop.addModifies(stmt5, y);
    pop.addUses(stmt5, x);
    pop.addUses(stmt5, y);
    shared_ptr<AssignStatement> stmt6 = make_shared<AssignStatement>(6, y, "main");
    pop.addNext(stmt3, stmt6);
    pop.addParent(stmt3, stmt6);
    pop.addModifies(stmt6, y);
    pop.addUses(stmt6, y);
    shared_ptr<AssignStatement> stmt7 = make_shared<AssignStatement>(7, y, "main");
    pop.addNext(stmt5, stmt7);
    pop.addNext(stmt6, stmt7);
    pop.addModifies(stmt7, y);
    pop.addUses(stmt7, x);
    pop.addUses(stmt7, y);
    shared_ptr<WhileStatement> stmt8 = make_shared<WhileStatement>(8, cond, "main");
    pop.addNext(stmt7, stmt8);
    pop.addUses(stmt8, y);
    shared_ptr<AssignStatement> stmt9 = make_shared<AssignStatement>(9, y, "main");
    stmt8->addStatement(stmt9);
    pop.addNext(stmt8, stmt9);
    pop.addParent(stmt8, stmt9);
    pop.addNext(stmt9, stmt8);
    pop.addUses(stmt9, y);
    pop.addModifies(stmt9, y);
    pop.tabulate();

    QueryManager qm;
    auto affects = qm.getAffects();
    REQUIRE(affects.size() == 10);
    qm.clear();
}