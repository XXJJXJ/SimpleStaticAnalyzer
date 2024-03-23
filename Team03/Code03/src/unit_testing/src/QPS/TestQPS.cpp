#include "catch.hpp"
#include "sp/sp.h"
#include "qps/QueryParser.h"
#include "qps/QueryEvaluator.h"
#include "qps/QueryTokenizer.h"
#include "qps/QueryValidator.h"
#include "qps/entity/evaluation/EvaluationPlanner.h"
#include "qps/entity/parser/SelectionsParser.h"
#include "qps/entity/parser/PredicateFactory.h"
#include "common/spa_exception/SemanticErrorException.h"
#include "qps/QpsManager.h"


// TODO: move this to integration test, but don't delete this for now, it's useful for debugging
TEST_CASE("Integration test") {
    auto sp = Sp();
    sp.ProcessSIMPLE("ms2_test1_source.txt");
    string query = "while w; Select w such that not Modifies(w, \"eggs\")";
    QpsManager qm;
    auto result = qm.processQuery(query);
    REQUIRE(result.size() == 2);
}