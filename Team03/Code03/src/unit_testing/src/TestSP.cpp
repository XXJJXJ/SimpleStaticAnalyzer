#include "catch.hpp"
#include "sp/sp.h"
#include "pkb/EntityManager.h"
#include "pkb/QueryPKB.h"

TEST_CASE("1st SP Test") {
	Sp sp = Sp();
    sp.ProcessSIMPLE("input.txt");

    QueryManager qm;
    vector<shared_ptr<Variable>> varStore = qm.getAllVariables();
    vector<shared_ptr<Procedure>> procStore = qm.getAllProcedures();
    vector<shared_ptr<ReadStatement>> readStore = qm.getAllReadStatements();
    vector<shared_ptr<PrintStatement>> printStore = qm.getAllPrintStatements();
    vector<shared_ptr<IfStatement>> ifStore = qm.getAllIfStatements();
    vector<shared_ptr<WhileStatement>> whileStore = qm.getAllWhileStatements();
    vector<vector<shared_ptr<Entity>>> followsStore = qm.getFollowS();
    vector<vector<shared_ptr<Entity>>> parentStore = qm.getParentS();
    vector<vector<shared_ptr<Entity>>> usesStore = qm.getUseAll();
    vector<vector<shared_ptr<Entity>>> modifiesStore = qm.getModifyAll();

    std::cout << "uses relations: " << usesStore.size() << std::endl;
    std::cout << "modifies relations: " << modifiesStore.size() << std::endl;

    bool result = varStore.size() == 3 && procStore.size() == 1 && readStore.size() == 1 && printStore.size() == 1;
    REQUIRE(result);
    EntityManager::clear();
}