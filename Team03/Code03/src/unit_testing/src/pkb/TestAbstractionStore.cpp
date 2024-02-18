#include "catch.hpp"

#include "common/Constant.h"
#include "common/Variable.h"
#include "common/Procedure.h"
#include "common/Statement.h"
#include "pkb/PopulatePKB.h"
#include "pkb/QueryPKB.h"
// Statement classes indirectly imported in QueryPKB.h

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
    auto followS = qm.getFollowS();
    REQUIRE((followS[stmt1].find(stmt2) != followS[stmt1].end()));
    REQUIRE((followS[stmt2].find(stmt3) != followS[stmt2].end()));
    REQUIRE((followS[stmt3].find(stmt4) != followS[stmt3].end()));

    auto followT = qm.getFollowT();
    REQUIRE((followT[stmt1].find(stmt2) != followT[stmt1].end()));
    REQUIRE((followT[stmt1].find(stmt3) != followT[stmt1].end()));
    REQUIRE((followT[stmt1].find(stmt4) != followT[stmt1].end()));

    REQUIRE((followT[stmt2].find(stmt3) != followT[stmt1].end()));
    REQUIRE((followT[stmt2].find(stmt4) != followT[stmt1].end()));

    REQUIRE((followT[stmt3].find(stmt4) != followT[stmt1].end()));
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
    auto parentS = qm.getParentS();
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

    auto parentT = qm.getParentT();
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
    auto modifiesAllStmt = qm.getModifyAll();
    REQUIRE((modifiesAllStmt[stmt4].find(y) == modifiesAllStmt[stmt4].end()));
    REQUIRE((modifiesAllStmt[stmt4].find(x) != modifiesAllStmt[stmt4].end()));

    auto modifiesAllRead = qm.getModifyByRead();
    REQUIRE((modifiesAllRead[stmt4].find(y) == modifiesAllRead[stmt4].end()));
    REQUIRE((modifiesAllRead[stmt4].find(x) != modifiesAllRead[stmt4].end()));

    auto modifiesByProcedure = qm.getModifyByProcedure();
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
    auto useAllStmt = qm.getUseAll();
    REQUIRE((useAllStmt[stmt3].find(y) != useAllStmt[stmt3].end()));
    REQUIRE((useAllStmt[stmt3].find(x) == useAllStmt[stmt3].end()));

    auto useAllPrint = qm.getUseByPrint();
    REQUIRE((useAllPrint[stmt3].find(y) != useAllPrint[stmt3].end()));
    REQUIRE((useAllPrint[stmt3].find(x) == useAllPrint[stmt3].end()));

    auto useByProcedure = qm.getUseByProcedure();
    REQUIRE((useByProcedure["main"].find(y) != useByProcedure["main"].end()));
    REQUIRE((useByProcedure["main"].find(x) == useByProcedure["main"].end()));
    pop.clear();
}