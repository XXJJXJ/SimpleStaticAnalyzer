#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"


// TODO: Remove this before final submission
//TEST_CASE("System test") {
//    auto sp = Sp();
//    sp.ProcessSIMPLE("milestone3_basic_multi_clause_source.txt");
//    string query = "stmt s; read r; print p;\n"
//                   "Select r.varName with p.varName  = r.varName and 5 = 5 and \"x\" = \"x\" and p.varName = \"number\"";
//    QpsManager qm;
//    auto result = qm.processQuery(query);
//    REQUIRE(result.size() == 1);
//}
