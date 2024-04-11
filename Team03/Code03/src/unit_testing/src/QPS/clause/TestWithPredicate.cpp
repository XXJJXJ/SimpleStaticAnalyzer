#include "catch.hpp"

#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/clause/WithPredicate.h"
#include "qps/entity/evaluation/HeaderTable.h"
#include "../fakeEntities/FakeQueryManager.cpp"


TEST_CASE("Test WithPredicate") {
    QueryEvaluationContext qec = QueryEvaluationContext();
    shared_ptr<FakeQueryManager> qm = make_shared<FakeQueryManager>();
    qec.setQueryManager(qm);
    shared_ptr<Constant> c1 = make_shared<Constant>("1");
    shared_ptr<Constant> c2 = make_shared<Constant>("2");
    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<AssignStatement> stmt1 = make_shared<AssignStatement>(1, x, "main");
    shared_ptr<PrintStatement> stmt2 = make_shared<PrintStatement>(2, y, "main");

    SECTION("Input validity checks") {
        SECTION("Valid with integers") {
            REQUIRE_NOTHROW(WithPredicate(Ref(1), Ref(1)));
        }

        SECTION("Valid with integer and statementNumber") {
            REQUIRE_NOTHROW(WithPredicate(Ref(1), Ref(stmt1->getStatementNumber())));
        }

        SECTION("Valid with statementNumber and integer") {
            REQUIRE_NOTHROW(WithPredicate(Ref(stmt2->getStatementNumber()), Ref(2)));
        }

        SECTION("Valid with integer and constant value") {
            REQUIRE_NOTHROW(WithPredicate(Ref(1), Ref(c1->getValue())));
        }

        SECTION("Valid with constant value and integer") {
            REQUIRE_NOTHROW(WithPredicate(Ref(c2->getValue()), Ref(2)));
        }

        SECTION("Valid with string and procedure name") {
            REQUIRE_NOTHROW(WithPredicate(Ref(std::string("main")), Ref(stmt1->getProcedureName())));
        }

        SECTION("Valid with procedure name and string") {
            REQUIRE_NOTHROW(WithPredicate(Ref(stmt2->getProcedureName()), Ref(std::string("main"))));
        }
        
        SECTION("Invalid with procedure name and integer") {
            REQUIRE_THROWS_AS(WithPredicate(Ref(stmt2->getProcedureName()), Ref(1)), SemanticErrorException);
        }

        SECTION("Invalid with statement number and string") {
            REQUIRE_THROWS_AS(WithPredicate(Ref(stmt1->getStatementNumber()), Ref(std::string("1"))), SemanticErrorException);
        }
    }
    /*
    SECTION("with 1 = a.stmt# gets 1 row") {
        WithPredicate withPred(Ref(1), Ref(stmt1->getStatementNumber()));
        auto table = withPred.getResultTable(qec);
        auto headerTable = dynamic_pointer_cast<HeaderTable>(table);
        REQUIRE(headerTable->getRows().size() == 1);
    }

    SECTION("with c.val = 1 gets 1 row") {
        WithPredicate withPred(Ref(c1->getName()), Ref(1));
        auto table = withPred.getResultTable(qec);
        auto headerTable = dynamic_pointer_cast<HeaderTable>(table);
        REQUIRE(headerTable->getRows().size() == 1);
    }
    */
}