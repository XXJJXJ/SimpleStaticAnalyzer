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
    vector<string>
        tok1 = {"abb", "=", "3", "+", "5", "-", "x", "*", "9109", "+", "111", "*", "10", "/", "5", "%", "3", ";"};
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
    vector<string> tok2 = {"ak", "=", "3", "+", "5", "-", "x", ";"};
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
    vector<string> tok3 = {"a", "=", "5", "-", "x", ";"};
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
        REQUIRE((qm.getAssignPattern("", false).size() == 0));
    }

    SECTION("Get empty var, empty expr, wildcard gets 3 statements") {
        REQUIRE((qm.getAssignPattern("", true).size() == 3));
    }

    SECTION("[Exact match] Get test empty var, expr, no wildcard") {
        // Only statement3
        REQUIRE((qm.getAssignPattern("5 - x", false).size() == 1));
        REQUIRE((qm.getAssignPattern("5-x", false).size() == 1));

        // No statement
        REQUIRE((qm.getAssignPattern("3 + 5", false).size() == 0));
        REQUIRE((qm.getAssignPattern("3+5", false).size() == 0));

        // Only statement 2
        REQUIRE((qm.getAssignPattern("3 + 5 - x", false).size() == 1));
        REQUIRE((qm.getAssignPattern("3+5-x", false).size() == 1));

        // Only statement 1
        REQUIRE((qm.getAssignPattern("3 + 5 - x * 9109 + 111 * 10 / 5 % 3", false).size() == 1));
        REQUIRE((qm.getAssignPattern("3+5-x*9109+111*10/5%3", false).size() == 1));
    }

    SECTION("[Partial match] Get empty var, expr, with wildcard, no parenthesis") {
        // Only statement3
        REQUIRE((qm.getAssignPattern("5 - x", true).size() == 1));
        REQUIRE((qm.getAssignPattern("5-x", true).size() == 1));

        // Statement 1 and 2
        REQUIRE((qm.getAssignPattern("3 + 5", true).size() == 2));
        REQUIRE((qm.getAssignPattern("3+5", true).size() == 2));
        REQUIRE((qm.getAssignPattern(" 3 ", true).size() == 2));
        REQUIRE((qm.getAssignPattern("3", true).size() == 2));

        // Only statement 2
        REQUIRE((qm.getAssignPattern("3 + 5 - x", true).size() == 1));
        REQUIRE((qm.getAssignPattern("3+5-x", true).size() == 1));

        // Only statement 1
        REQUIRE((qm.getAssignPattern("111 * 10", true).size() == 1));
        REQUIRE((qm.getAssignPattern("111 * 10 / 5", true).size() == 1));
        REQUIRE((qm.getAssignPattern("111 * 10 / 5 % 3", true).size() == 1));
        REQUIRE((qm.getAssignPattern("3+5-x*9109+111*10/5%3", true).size() == 1));

        // All 3 statements
        REQUIRE((qm.getAssignPattern(" 5 ", true).size() == 3));
        REQUIRE((qm.getAssignPattern("5", true).size() == 3));

        // No statements
        REQUIRE((qm.getAssignPattern("9109 + 111", true).size() == 0));
        REQUIRE((qm.getAssignPattern("5 % 3", true).size() == 0));
    }

    SECTION("[Partial match] Get empty var, expr, with wildcard, with parenthesis") {
        // Only statement3
        REQUIRE((qm.getAssignPattern("(5) - (x)", true).size() == 1));
        REQUIRE((qm.getAssignPattern("(5-x)", true).size() == 1));
        REQUIRE((qm.getAssignPattern("((5)-(x))", true).size() == 1));

        // Statement 1 and 2
        REQUIRE((qm.getAssignPattern("(3) + (5)", true).size() == 2));
        REQUIRE((qm.getAssignPattern("(3+5)", true).size() == 2));
        REQUIRE((qm.getAssignPattern(" (3 )", true).size() == 2));
        REQUIRE((qm.getAssignPattern("(3)", true).size() == 2));

        // Only statement 2
        REQUIRE((qm.getAssignPattern("(3 + 5) - x", true).size() == 1));
        REQUIRE((qm.getAssignPattern("3+(5)-x", true).size() == 1));

        // Only statement 1
        REQUIRE((qm.getAssignPattern("(111) * (10)", true).size() == 1));
        REQUIRE((qm.getAssignPattern("(111 * 10) / 5", true).size() == 1));
        REQUIRE((qm.getAssignPattern("((111 * (10)) / 5)", true).size() == 1));
        REQUIRE((qm.getAssignPattern("((111 * 10) / 5 % 3)", true).size() == 1));
        // No statement because of parenthesis
        REQUIRE((qm.getAssignPattern("((111 * 10) / (5 % 3))", true).size() == 0));

        REQUIRE((qm.getAssignPattern("(3+5)-(x*9109)+(111*10/5%3)", true).size() == 1));
        // None because of parenthesis
        REQUIRE((qm.getAssignPattern("(3+5)-((x*9109)+(111*10/5%3))", true).size() == 0));

        // All 3 statements
        REQUIRE((qm.getAssignPattern("( 5 )", true).size() == 3));
    }

    qm.clear();
    // Check cleared
}

TEST_CASE("Store detect pattern in if statement") {
    Populator pop;
    pop.clear();

    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<Variable> z = make_shared<Variable>("z");
    // bare minimal for test
    shared_ptr<ConditionalOperation> cond = make_shared<ConditionalOperation>("test_expression", make_pair<>(x, y));
    shared_ptr<IfStatement> stmt1 = make_shared<IfStatement>(1, cond, "main");
    shared_ptr<IfStatement> stmt6 = make_shared<IfStatement>(6, cond, "main");
    pop.addIfStatement(stmt1);
    pop.addIfStatement(stmt6);
    pop.addUses(stmt1, x);
    pop.addUses(stmt1, y);
    pop.addUses(stmt6, x);
    pop.addUses(stmt6, z);

    QueryManager qm;
    REQUIRE(qm.getIfPattern().size() == 4);

    qm.clear();
}

TEST_CASE("Store detect pattern in while statement") {
    Populator pop;
    pop.clear();

    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<Variable> z = make_shared<Variable>("z");
    // bare minimal for test
    shared_ptr<ConditionalOperation> cond = make_shared<ConditionalOperation>("test_expression", make_pair<>(x, y));
    shared_ptr<WhileStatement> stmt1 = make_shared<WhileStatement>(1, cond, "main");
    shared_ptr<WhileStatement> stmt6 = make_shared<WhileStatement>(6, cond, "main");
    pop.addUses(stmt1, x);
    pop.addUses(stmt1, y);
    pop.addUses(stmt6, x);
    pop.addUses(stmt6, z);

    QueryManager qm;
    REQUIRE(qm.getWhilePattern().size() == 4);

    qm.clear();
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
    SECTION("Clears Assignment Pattern Store properly") {
        pop.addAssignStatement(assignStmt3);
        REQUIRE((qm.getAssignPattern("", true).size() == 1));
        qm.clear();
        REQUIRE((qm.getAssignPattern("", true).size() == 0));
    }

    shared_ptr<Variable> x = make_shared<Variable>("x");
    shared_ptr<Variable> y = make_shared<Variable>("y");
    shared_ptr<ConditionalOperation> cond = make_shared<ConditionalOperation>("test_expression", make_pair<>(x, y));
    SECTION("Clears If Pattern Store properly") {
        shared_ptr<IfStatement> ifStmt = make_shared<IfStatement>(1, cond, "main");
        pop.addIfStatement(ifStmt);
        pop.addUses(ifStmt, x);
        REQUIRE((qm.getIfPattern().size() == 1));
        qm.clear();
        REQUIRE((qm.getIfPattern().size() == 0));
    }

    SECTION("Clears While Pattern Store properly") {
        shared_ptr<WhileStatement> whileStmt = make_shared<WhileStatement>(1, cond, "main");
        pop.addWhileStatement(whileStmt);
        pop.addUses(whileStmt, x);
        REQUIRE((qm.getWhilePattern().size() == 1));
        qm.clear();
        REQUIRE((qm.getWhilePattern().size() == 0));
    }
}