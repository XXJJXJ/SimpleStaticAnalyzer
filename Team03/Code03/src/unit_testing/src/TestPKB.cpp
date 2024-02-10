#include "catch.hpp"
#include "common/Variable.h"
#include "common/Procedure.h"
#include "pkb/PopulatePKB.h"
#include "pkb/QueryPKB.h"
#include "pkb/EntityManager.h"

using namespace std;

TEST_CASE("Store and retrieve Variables") {
    EntityManager::clear();
    Populator populator;
    shared_ptr<Variable> v = make_shared<Variable>("x");
    populator.addVariable(v);
    QueryMananger queryM;
    vector<shared_ptr<Variable>> varStore = queryM.getAllVariables();
    REQUIRE(varStore.size() == 1);
    shared_ptr<Variable> v2 = varStore.front();
    REQUIRE(v2->getName() == "x");
    REQUIRE(v2 == v);
    EntityManager::clear();
}

TEST_CASE("Store duplicate variables") {
    EntityManager::clear();
    Populator populator;
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> x_dup = make_shared<Variable>("x");
    populator.addVariable(x);
    populator.addVariable(x_dup);
    QueryMananger queryM;
    vector<shared_ptr<Variable>> varStore = queryM.getAllVariables();
    shared_ptr<Variable> x2 = varStore.front();
    REQUIRE((x2->getName() == "x"));
    REQUIRE(varStore.size() == 1);
    shared_ptr<Variable> y = make_shared<Variable>("y");
    populator.addVariable(y);
    varStore = queryM.getAllVariables();
    REQUIRE(varStore.size() == 2);
    REQUIRE((varStore[1]->getName() == "y" || varStore[0]->getName() == "y"));
    EntityManager::clear();
}

TEST_CASE("Store and retrieve procedures") {
    EntityManager::clear();
    Populator populator;
    QueryMananger queryM;
    shared_ptr<Procedure> proc1 = make_shared<Procedure>("main1");
    shared_ptr<Procedure> proc2 = make_shared<Procedure>("main2");
    shared_ptr<Procedure> proc3 = make_shared<Procedure>("main3");
    populator.addProcedure(proc1);
    populator.addProcedure(proc2);
    populator.addProcedure(proc3);
    vector<shared_ptr<Procedure>> procList = queryM.getAllProcedures();
    REQUIRE(procList.size() == 3);
    // check names
    unordered_set<string> set;
    for (int i = 0; i < 3; i++) {
        shared_ptr<Procedure> proc = procList[i];
        set.insert(proc->getProcedureName());
    }
    REQUIRE(set.size() == 3);
    for (int i = 0; i < 3; i++) {
        string name = "main" + to_string(i + 1);
        REQUIRE(set.find(name) != set.end());
    }
    EntityManager::clear();
}

TEST_CASE("Store duplicate procedures") {
    EntityManager::clear();
    Populator populator;
    QueryMananger queryM;
    shared_ptr<Procedure> proc1 = make_shared<Procedure>("main");
    REQUIRE(populator.addProcedure(proc1)); // Successful return true

    // This is duplicate, fail to add
    shared_ptr<Procedure> proc2 = make_shared<Procedure>("main");
    REQUIRE(!populator.addProcedure(proc2)); // Should return false

    // Non duplicate, succeed
    shared_ptr<Procedure> proc3 = make_shared<Procedure>("second");
    REQUIRE(populator.addProcedure(proc3)); // Should return true

    REQUIRE(queryM.getAllProcedures().size() == 2);
    EntityManager::clear();
}

TEST_CASE("Store and retrieve read statements") {
    EntityManager::clear();
    Populator populator;
    QueryMananger queryM;
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<ReadStatement> readX = make_shared<ReadStatement>(1, x, "main");
    shared_ptr<ReadStatement> readY = make_shared<ReadStatement>(2, y, "main");
    populator.addReadStatement(readX);
    populator.addReadStatement(readY);
    vector<shared_ptr<ReadStatement>> stmtLst = queryM.getAllReadStatements();
    REQUIRE(stmtLst.size() == 2);
    unordered_set<string> set;
    for (int i = 0; i < 2; i++) {
        shared_ptr<ReadStatement> stmt = stmtLst[i];
        set.insert(stmt->getVariable()->getName());
        REQUIRE(stmt->getProcedureName() == "main");
    }
    REQUIRE(set.size() == 2);
    REQUIRE(set.find("y") != set.end());
    REQUIRE(set.find("x") != set.end());
    EntityManager::clear();
}

TEST_CASE("Store and retrieve print statements") {
    EntityManager::clear();
    Populator populator;
    QueryMananger queryM;
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<PrintStatement> printX = make_shared<PrintStatement>(1, x, "main");
    shared_ptr<PrintStatement> printY = make_shared<PrintStatement>(2, y, "main");
    populator.addPrintStatement(printX);
    populator.addPrintStatement(printY);
    vector<shared_ptr<PrintStatement>> stmtLst = queryM.getAllPrintStatements();
    REQUIRE(stmtLst.size() == 2);
    unordered_set<string> set;
    for (int i = 0; i < 2; i++) {
        shared_ptr<PrintStatement> stmt = stmtLst[i];
        set.insert(stmt->getVariable()->getName());
        REQUIRE(stmt->getProcedureName() == "main");
    }
    REQUIRE(set.size() == 2);
    REQUIRE(set.find("y") != set.end());
    REQUIRE(set.find("x") != set.end());
    EntityManager::clear();
}

TEST_CASE("Store duplicate statements") {
    EntityManager::clear();
    Populator populator;
    QueryMananger queryM;

    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<PrintStatement> printX = make_shared<PrintStatement>(1, x, "main");
    shared_ptr<ReadStatement> readY = make_shared<ReadStatement>(2, y, "main");
    
    REQUIRE(populator.addPrintStatement(printX));
    REQUIRE(populator.addReadStatement(readY));

    // impossible duplicates
    shared_ptr<ReadStatement> readX = make_shared<ReadStatement>(1, x, "main");
    shared_ptr<PrintStatement> printY = make_shared<PrintStatement>(2, y, "main");
    // Should return false
    REQUIRE(!populator.addReadStatement(readX));
    REQUIRE(!populator.addPrintStatement(printY));

    vector<shared_ptr<PrintStatement>> printStmtLst = queryM.getAllPrintStatements();
    REQUIRE(printStmtLst.size() == 1);
    vector<shared_ptr<ReadStatement>> readStmtLst = queryM.getAllReadStatements();
    REQUIRE(readStmtLst.size() == 1);
    vector<shared_ptr<Statement>> allStmtLst = queryM.getAllStatements();
    REQUIRE(allStmtLst.size() == 2);
    EntityManager::clear();
}

TEST_CASE("Clear store") {
    EntityManager::clear(); // Ensure other failed test cases do not affect this case
    Populator populator;
    QueryMananger queryM;
    REQUIRE(queryM.getAllVariables().size() == 0);
    shared_ptr<Variable> v = make_shared<Variable>("x");
    populator.addVariable(v);
    REQUIRE(queryM.getAllVariables().size() == 1);
    shared_ptr<Procedure> proc = make_shared<Procedure>("main");
    populator.addProcedure(proc);
    REQUIRE(queryM.getAllProcedures().size() == 1);
    shared_ptr<ReadStatement> read = make_shared<ReadStatement>(1, v, "main");
    populator.addReadStatement(read);
    REQUIRE(queryM.getAllReadStatements().size() == 1);
    EntityManager::clear();
    REQUIRE(queryM.getAllVariables().size() == 0);
    REQUIRE(queryM.getAllProcedures().size() == 0);
}
// TEST_CASE("Test store and retrieve Constants") {
//     Populator populator;
//     shared_ptr<Constant> c = make_shared<Constant>(2);
//     populator.addConstant(c);
//     QueryMananger queryM;
//     vector<shared_ptr<Constant>> constStore = queryM.getAllConstants();
//     REQUIRE(constStore.size() == 1);
//     shared_ptr<Constant> c2 = constStore.front();
//     REQUIRE(c2->getValue() == 2);
//     REQUIRE(c2 == c);
//     EntityManager::clear();
// }

// TEST_CASE("Test Store duplicate constants") {
//     EntityManager::clear();
//     Populator populator;
//     shared_ptr<Constant> c = make_shared<Constant>(2);
//     shared_ptr<Constant> c_dup = make_shared<Constant>(2);
//     populator.addConstant(c);
//     populator.addConstant(c_dup);
//     QueryMananger queryM;
//     vector<shared_ptr<Constant>> constStore = queryM.getAllConstants();
//     REQUIRE(constStore.size() == 1);
//     shared_ptr<Constant> c2 = constStore.front();
//     REQUIRE(c2->getValue() == 2);
//     shared_ptr<Constant> c3 = make_shared<Constant>(3);
//     populator.addConstant(c3);
//     constStore = queryM.getAllConstants();
//     REQUIRE(constStore.size() == 2);
//     REQUIRE((constStore[1]->getValue() == 3 || constStore[0]->getValue() == 3)); // it is unordered, so the vector is unordered
//     EntityManager::clear();
// }