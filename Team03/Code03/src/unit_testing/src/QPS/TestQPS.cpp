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


// TODO: move this to integration test, but don't delete this for now, it's useful for debugging
//TEST_CASE("Integration test") {
//    auto sp = Sp();
//    sp.ProcessSIMPLE("milestone1_modifiesp_usesp_call_source.txt");
//    string query = "stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; procedure p, q; constant c; read re; print pn; call cl;\n"
//                   "Select <a, a>";
//    QueryTokenizer qt;
//    QueryParser qp;
//    QueryValidator qv;
//    std::vector<std::vector<std::vector<std::string>>> tokens = qt.tokenize(query);
//    auto validatedTokens = qv.validate(tokens);
//    REQUIRE_NOTHROW(qp.parse(validatedTokens));
//    auto q = qp.parse(validatedTokens);
//    auto qe = make_shared<QueryEvaluator>();
//
//    EvaluationPlanner ep = EvaluationPlanner(q, qe);
//    ep.plan();
//    auto res = qe->evaluate(q);
//    REQUIRE(res.size() == 11);
//}