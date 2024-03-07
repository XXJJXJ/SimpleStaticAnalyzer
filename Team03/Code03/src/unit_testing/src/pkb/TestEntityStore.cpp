#include "catch.hpp"

#include "common/Constant.h"
#include "common/Variable.h"
#include "common/Procedure.h"
#include "common/Statement.h"
#include "pkb/PopulatePKB.h"
#include "pkb/QueryPKB.h"

using namespace std;

TEST_CASE("Store and retrieve Variables") {
    Populator populator;
    populator.clear();
    shared_ptr<Variable> v = make_shared<Variable>("x");
    populator.addVariable(v);
    QueryManager queryM;
    vector<shared_ptr<Entity>> varStore = queryM.getAllEntitiesByType(EntityType::Variable);
    REQUIRE(varStore.size() == 1);
    shared_ptr<Variable> v2 = dynamic_pointer_cast<Variable>(varStore.front());
    REQUIRE(v2->getName() == "x");
    REQUIRE(v2 == v);
    populator.clear();
}

TEST_CASE("Store duplicate variables") {
    Populator populator;
    populator.clear();
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> x_dup = make_shared<Variable>("x");
    populator.addVariable(x);
    populator.addVariable(x_dup);
    QueryManager queryM;
    vector<shared_ptr<Entity>> varStore = queryM.getAllEntitiesByType(EntityType::Variable);
    shared_ptr<Variable> x2 = dynamic_pointer_cast<Variable>(varStore.front());
    REQUIRE((x2->getName() == "x"));
    REQUIRE(varStore.size() == 1);
    shared_ptr<Variable> y = make_shared<Variable>("y");
    populator.addVariable(y);
    varStore = queryM.getAllEntitiesByType(EntityType::Variable);
    REQUIRE(varStore.size() == 2);
    REQUIRE((varStore[1]->getName() == "y" || varStore[0]->getName() == "y"));
    populator.clear();
}

TEST_CASE("Store and retrieve procedures") {
    Populator populator;
    populator.clear();
    QueryManager queryM;
    shared_ptr<Procedure> proc1 = make_shared<Procedure>("main1");
    shared_ptr<Procedure> proc2 = make_shared<Procedure>("main2");
    shared_ptr<Procedure> proc3 = make_shared<Procedure>("main3");
    populator.addProcedure(proc1);
    populator.addProcedure(proc2);
    populator.addProcedure(proc3);
    vector<shared_ptr<Entity>> procList = queryM.getAllEntitiesByType(EntityType::Procedure);
    REQUIRE(procList.size() == 3);
    // check names
    unordered_set<string> set;
    for (int i = 0; i < 3; i++) {
        shared_ptr<Entity> proc = procList[i];
        set.insert(proc->getName());
    }
    REQUIRE(set.size() == 3);
    for (int i = 0; i < 3; i++) {
        string name = "main" + to_string(i + 1);
        REQUIRE(set.find(name) != set.end());
    }
    populator.clear();
}

TEST_CASE("Store duplicate procedures") {
    Populator populator;
    populator.clear();
    QueryManager queryM;
    shared_ptr<Procedure> proc1 = make_shared<Procedure>("main");
    REQUIRE(populator.addProcedure(proc1)); // Successful return true

    // This is duplicate, fail to add
    shared_ptr<Procedure> proc2 = make_shared<Procedure>("main");
    REQUIRE(!populator.addProcedure(proc2)); // Should return false

    // Non duplicate, succeed
    shared_ptr<Procedure> proc3 = make_shared<Procedure>("second");
    REQUIRE(populator.addProcedure(proc3)); // Should return true

    REQUIRE(queryM.getAllEntitiesByType(EntityType::Procedure).size() == 2);
    populator.clear();
}

TEST_CASE("Store and retrieve read statements") {
    Populator populator;
    populator.clear();
    QueryManager queryM;
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<ReadStatement> readX = make_shared<ReadStatement>(1, x, "main");
    shared_ptr<ReadStatement> readY = make_shared<ReadStatement>(2, y, "main");
    populator.addReadStatement(readX);
    populator.addReadStatement(readY);
    vector<shared_ptr<Entity>> stmtLst = queryM.getAllEntitiesByType(EntityType::Read);
    REQUIRE(stmtLst.size() == 2);
    unordered_set<string> set;
    for (int i = 0; i < 2; i++) {
        shared_ptr<ReadStatement> stmt = dynamic_pointer_cast<ReadStatement>(stmtLst[i]);
        set.insert(stmt->getVariable()->getName());
        REQUIRE(stmt->getProcedureName() == "main");
    }
    REQUIRE(set.size() == 2);
    REQUIRE(set.find("y") != set.end());
    REQUIRE(set.find("x") != set.end());
    populator.clear();
}

TEST_CASE("Store and retrieve print statements") {
    Populator populator;
    populator.clear();
    QueryManager queryM;
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<PrintStatement> printX = make_shared<PrintStatement>(1, x, "main");
    shared_ptr<PrintStatement> printY = make_shared<PrintStatement>(2, y, "main");
    populator.addPrintStatement(printX);
    populator.addPrintStatement(printY);
    vector<shared_ptr<Entity>> stmtLst = queryM.getAllEntitiesByType(EntityType::Print);
    REQUIRE(stmtLst.size() == 2);
    unordered_set<string> set;
    for (int i = 0; i < 2; i++) {
        shared_ptr<PrintStatement> stmt = dynamic_pointer_cast<PrintStatement>(stmtLst[i]);
        set.insert(stmt->getVariable()->getName());
        REQUIRE(stmt->getProcedureName() == "main");
    }
    REQUIRE(set.size() == 2);
    REQUIRE(set.find("y") != set.end());
    REQUIRE(set.find("x") != set.end());
    populator.clear();
}

TEST_CASE("Store duplicate statements") {
    Populator populator;
    populator.clear();
    QueryManager queryM;

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

    vector<shared_ptr<Entity>> printStmtLst = queryM.getAllEntitiesByType(EntityType::Print);;
    REQUIRE(printStmtLst.size() == 1);
    vector<shared_ptr<Entity>> readStmtLst = queryM.getAllEntitiesByType(EntityType::Read);;
    REQUIRE(readStmtLst.size() == 1);
    vector<shared_ptr<Entity>> allStmtLst = queryM.getAllEntitiesByType(EntityType::Stmt);
    REQUIRE(allStmtLst.size() == 2);
    populator.clear();
}

TEST_CASE("Clear store") {
    Populator populator;
    populator.clear();
    QueryManager queryM;
    REQUIRE(queryM.getAllEntitiesByType(EntityType::Variable).size() == 0);
    shared_ptr<Variable> v = make_shared<Variable>("x");
    populator.addVariable(v);
    REQUIRE(queryM.getAllEntitiesByType(EntityType::Variable).size() == 1);
    shared_ptr<Procedure> proc = make_shared<Procedure>("main");
    populator.addProcedure(proc);
    REQUIRE(queryM.getAllEntitiesByType(EntityType::Procedure).size() == 1);
    shared_ptr<ReadStatement> read = make_shared<ReadStatement>(1, v, "main");
    populator.addReadStatement(read);
    REQUIRE(queryM.getAllEntitiesByType(EntityType::Read).size() == 1);
    populator.clear();
    REQUIRE(queryM.getAllEntitiesByType(EntityType::Variable).size() == 0);
    REQUIRE(queryM.getAllEntitiesByType(EntityType::Procedure).size() == 0);
}

TEST_CASE("Test store and retrieve Constants") {
    Populator populator;
    populator.clear();
    shared_ptr<Constant> c = make_shared<Constant>("2");
    populator.addConstant(c);
    QueryManager queryM;
    vector<shared_ptr<Entity>> constStore = queryM.getAllEntitiesByType(EntityType::Constant);
    REQUIRE(constStore.size() == 1);
    shared_ptr<Constant> c2 = dynamic_pointer_cast<Constant>(constStore.front());
    REQUIRE(c2->getName() == "2");
    REQUIRE(c2 == c);
    populator.clear();
}

TEST_CASE("Test Store duplicate constants") {
    Populator populator;
    populator.clear();
    shared_ptr<Constant> c = make_shared<Constant>("2");
    shared_ptr<Constant> c_dup = make_shared<Constant>("2");
    populator.addConstant(c);
    populator.addConstant(c_dup);
    QueryManager queryM;
    vector<shared_ptr<Entity>> constStore = queryM.getAllEntitiesByType(EntityType::Constant);
    REQUIRE(constStore.size() == 1);
    shared_ptr<Constant> c2 = dynamic_pointer_cast<Constant>(constStore.front());
    REQUIRE(c2->getName() == "2");
    shared_ptr<Constant> c3 = make_shared<Constant>("3");
    populator.addConstant(c3);
    constStore = queryM.getAllEntitiesByType(EntityType::Constant);
    REQUIRE(constStore.size() == 2);
    REQUIRE((constStore[1]->getName() == "3" || constStore[0]->getName() == "3")); // it is unordered, so the vector is unordered
    populator.clear();
}