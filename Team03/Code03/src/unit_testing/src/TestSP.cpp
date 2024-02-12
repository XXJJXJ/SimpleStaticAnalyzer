#include "catch.hpp"
#include "sp/sp.h"
#include "pkb/QueryPKB.h"

TEST_CASE("1st SP Test") {
	Sp sp = Sp();
    sp.ProcessSIMPLE("input.txt");

    QueryManager qm;
    vector<shared_ptr<Variable>> varStore = qm.getAllVariables();
    vector<shared_ptr<Procedure>> procStore = qm.getAllProcedures();
    vector<shared_ptr<ReadStatement>> readStore = qm.getAllReadStatements();
    vector<shared_ptr<PrintStatement>> printStore = qm.getAllPrintStatements();

    std::cout << "Procedure: " << procStore.front()->getProcedureName() << std::endl;
    std::cout << "variable: " << varStore.front()->getName() << std::endl;
    std::cout << "read statement no.: " << readStore.front()->getStatementNumber() << std::endl;
    std::cout << "print statement no.: " << printStore.front()->getStatementNumber() << std::endl;

    bool result = varStore.size() == 1 && procStore.size() == 1 && readStore.size() == 1 && printStore.size() == 1;
    REQUIRE(result);
}