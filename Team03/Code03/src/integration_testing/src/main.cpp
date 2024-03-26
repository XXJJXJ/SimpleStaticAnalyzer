#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "sp/sp.h"
#include "qps/QueryTokenizer.h"
#include "qps/entity/parser/SelectionsParser.h"
#include "qps/QpsManager.h"


//TEST_CASE("System test") {
//    auto sp = Sp();
//    sp.ProcessSIMPLE("ms2_test1_source.txt");
//    string query = "while w; Select w such that not Modifies(w, \"eggs\")";
//    QpsManager qm;
//    auto result = qm.processQuery(query);
//    REQUIRE(result.size() == 2);
//}
