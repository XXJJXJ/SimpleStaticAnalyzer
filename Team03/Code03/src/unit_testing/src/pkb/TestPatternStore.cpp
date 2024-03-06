#include "catch.hpp"

#include <iostream>
#include "pkb/PopulatePKB.h"
#include "pkb/QueryPKB.h"
#include "sp/parser/AssignStatementParser.h"
#include "sp/tokenizer/Tokenizer.h"


using namespace std;


TEST_CASE("Store detect pattern in assignment") {
    
    AssignStatementParser parser;
    Tokenizer tker;
    // abb = 3 + 5 - x * 9109 + 111 * 10 / 5 % 3;
    /* ============= Tree should look like ================
                                +
                           /          \
                          -              %
                        /   \            /   \
                       +     *          /      3
                      / \   /  \       /  \
                     3  5  x   9109   *     5
                                    /   \
                                   111  10
    */
    vector<string> tok1 = {"abb", "=", "3", "+", "5", "-", "x", "*", "9109", "+", "111", "*", "10", "/", "5", "%", "3", ";"};
    Tokens tokens1;
    for (auto t : tok1) {
        tokens1.push_back(tker.stringToToken(t));
    }
    // ak = 3 + 5 - x;
    /* ============= Tree should look like ================
                        -
                      /   \
                     +     x
                    /  \
                   3    5  
    */
    vector<string> tok2 = {"ak", "=", "3", "+", "5", "-", "x",";"};
    Tokens tokens2;
    for (auto t : tok2) {
        tokens2.push_back(tker.stringToToken(t));
    }
    // a = 5 - x;
    /* ============= Tree should look like ================
                        -
                      /   \
                     5     x  
    */
    vector<string> tok3 = {"a", "=", "5", "-", "x",";"};
    Tokens tokens3;
    for (auto t : tok3) {
        tokens3.push_back(tker.stringToToken(t));
    }

    auto assignStmt1 = dynamic_pointer_cast<AssignStatement>(parser.parseEntity(tokens1));
    auto assignStmt2 = dynamic_pointer_cast<AssignStatement>(parser.parseEntity(tokens2));
    auto assignStmt3 = dynamic_pointer_cast<AssignStatement>(parser.parseEntity(tokens3));
    Populator pop;
    pop.addAssignStatement(assignStmt1);
    pop.addAssignStatement(assignStmt2);
    pop.addAssignStatement(assignStmt3);
    QueryManager qm;
    SECTION("Get empty var, empty expr, no wildcard gets nothing") {
        REQUIRE((qm.getAssignPattern("", "", false).size() == 0));
    }

    SECTION("Get empty var, empty expr, wildcard gets 3 statements") {
        REQUIRE((qm.getAssignPattern("", "", true).size() == 3));
    }

    SECTION("[Exact match] Get test empty var, expr, no wildcard") {
        // Only statement3
        REQUIRE((qm.getAssignPattern("", "5 - x", false).size() == 1));
        REQUIRE((qm.getAssignPattern("", "5-x", false).size() == 1));

        // No statement
        REQUIRE((qm.getAssignPattern("", "3 + 5", false).size() == 0));
        REQUIRE((qm.getAssignPattern("", "3+5", false).size() == 0));

        // Only statement 2
        REQUIRE((qm.getAssignPattern("", "3 + 5 - x", false).size() == 1));
        REQUIRE((qm.getAssignPattern("", "3+5-x", false).size() == 1));

        // Only statement 1
        REQUIRE((qm.getAssignPattern("", "3 + 5 - x * 9109 + 111 * 10 / 5 % 3", false).size() == 1));
        REQUIRE((qm.getAssignPattern("", "3+5-x*9109+111*10/5%3", false).size() == 1));
    }

    SECTION("[Partial match] Get empty var, expr, with wildcard, no parenthesis") {
        // Only statement3
        REQUIRE((qm.getAssignPattern("", "5 - x", true).size() == 1));
        REQUIRE((qm.getAssignPattern("", "5-x", true).size() == 1));

        // Statement 1 and 2
        REQUIRE((qm.getAssignPattern("", "3 + 5", true).size() == 2));
        REQUIRE((qm.getAssignPattern("", "3+5", true).size() == 2));
        REQUIRE((qm.getAssignPattern("", " 3 ", true).size() == 2));
        REQUIRE((qm.getAssignPattern("", "3", true).size() == 2));

        // Only statement 2
        REQUIRE((qm.getAssignPattern("", "3 + 5 - x", true).size() == 1));
        REQUIRE((qm.getAssignPattern("", "3+5-x", true).size() == 1));

        // Only statement 1
        REQUIRE((qm.getAssignPattern("", "111 * 10", true).size() == 1));
        REQUIRE((qm.getAssignPattern("", "111 * 10 / 5", true).size() == 1));
        REQUIRE((qm.getAssignPattern("", "111 * 10 / 5 % 3", true).size() == 1));
        REQUIRE((qm.getAssignPattern("", "3+5-x*9109+111*10/5%3", true).size() == 1));

        // All 3 statements
        REQUIRE((qm.getAssignPattern("", " 5 ", true).size() == 3));
        REQUIRE((qm.getAssignPattern("", "5", true).size() == 3));

        // No statements
        REQUIRE((qm.getAssignPattern("", "9109 + 111", true).size() == 0));
        REQUIRE((qm.getAssignPattern("", "5 % 3", true).size() == 0));
    }

    SECTION("[Partial match] Get empty var, expr, with wildcard, with parenthesis") {
        // Only statement3
        REQUIRE((qm.getAssignPattern("", "(5) - (x)", true).size() == 1));
        REQUIRE((qm.getAssignPattern("", "(5-x)", true).size() == 1));
        REQUIRE((qm.getAssignPattern("", "((5)-(x))", true).size() == 1));

        // Statement 1 and 2
        REQUIRE((qm.getAssignPattern("", "(3) + (5)", true).size() == 2));
        REQUIRE((qm.getAssignPattern("", "(3+5)", true).size() == 2));
        REQUIRE((qm.getAssignPattern("", " (3 )", true).size() == 2));
        REQUIRE((qm.getAssignPattern("", "(3)", true).size() == 2));

        // Only statement 2
        REQUIRE((qm.getAssignPattern("", "(3 + 5) - x", true).size() == 1));
        REQUIRE((qm.getAssignPattern("", "3+(5)-x", true).size() == 1));

        // Only statement 1
        REQUIRE((qm.getAssignPattern("", "(111) * (10)", true).size() == 1));
        REQUIRE((qm.getAssignPattern("", "(111 * 10) / 5", true).size() == 1));
        REQUIRE((qm.getAssignPattern("", "((111 * (10)) / 5)", true).size() == 1));
        REQUIRE((qm.getAssignPattern("", "((111 * 10) / 5 % 3)", true).size() == 1));
        // No statement because of parenthesis
        REQUIRE((qm.getAssignPattern("", "((111 * 10) / (5 % 3))", true).size() == 0));

        REQUIRE((qm.getAssignPattern("", "(3+5)-(x*9109)+(111*10/5%3)", true).size() == 1));
        // None because of parenthesis
        REQUIRE((qm.getAssignPattern("", "(3+5)-((x*9109)+(111*10/5%3))", true).size() == 0));

        // All 3 statements
        REQUIRE((qm.getAssignPattern("", "( 5 )", true).size() == 3));
    }

    SECTION("[Partial match] Get named var, expr, with wildcard") {
        // Statement 1
        REQUIRE((qm.getAssignPattern("abb", "3 + 5", true).size() == 1));
        REQUIRE((qm.getAssignPattern("abb", " 3 ", true).size() == 1));
        // Statement 2
        REQUIRE((qm.getAssignPattern("ak", "3+5", true).size() == 1));
        REQUIRE((qm.getAssignPattern("ak", " 3 ", true).size() == 1));
        // None
        REQUIRE((qm.getAssignPattern("aky", "3+5", true).size() == 0));
        REQUIRE((qm.getAssignPattern("bb", "3", true).size() == 0));

        // Only statement 2
        REQUIRE((qm.getAssignPattern("ak", "3 + 5 - x", true).size() == 1));
        // Var no match
        REQUIRE((qm.getAssignPattern("ac", "3+5-x", true).size() == 0));

        // Statement 1
        REQUIRE((qm.getAssignPattern("abb", " 5 ", true).size() == 1));
        // Statement 2
        REQUIRE((qm.getAssignPattern("ak", " 5 ", true).size() == 1));
        // Statement 3
        REQUIRE((qm.getAssignPattern("a", "5", true).size() == 1));
        // None
        REQUIRE((qm.getAssignPattern("aggg", "5", true).size() == 0));

        // Only statement 1
        REQUIRE((qm.getAssignPattern("abb", "3 + 5 - x * 9109 + 111 * 10 / 5 % 3", true).size() == 1));
        // None
        REQUIRE((qm.getAssignPattern("pih", "3+5-x*9109+111*10/5%3", true).size() == 0));
    }
    
    qm.clear();
    // Check cleared
}

TEST_CASE("Check clear") {
    AssignStatementParser parser;
    Tokenizer tker;
    vector<string> tok3 = {"a", "=", "5", "-", "x", ";"};
    Tokens tokens3;
    for (auto t : tok3) {
        tokens3.push_back(tker.stringToToken(t));
    }
    auto assignStmt3 = dynamic_pointer_cast<AssignStatement>(parser.parseEntity(tokens3));
    Populator pop;
    QueryManager qm;
    qm.clear(); // In case other test case affects
    pop.addAssignStatement(assignStmt3);
    REQUIRE((qm.getAssignPattern("", "", true).size() == 1));
    qm.clear();
    REQUIRE((qm.getAssignPattern("", "", true).size() == 0));
}