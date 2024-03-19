#include "catch.hpp"
#include "sp/sp.h"
#include "pkb/EntityManager.h"
#include "pkb/QueryPKB.h"
#include "sp/tokenizer/IntegerToken.h"
#include "sp/tokenizer/ArithmeticToken.h"
#include "sp/tokenizer/NameToken.h"
#include "sp/tokenizer/PunctuationToken.h"
#include "sp/parser/ExpressionParserFactory.h"
#include "sp/parser/IfStatementParser.h"


TEST_CASE("Check if ExtractCondition works") {
    Tokens if_line_valid
    { make_shared<NameToken>("if"), make_shared<PunctuationToken>("("),
     make_shared<NameToken>("x"), make_shared<PunctuationToken>(">"),
     make_shared<IntegerToken>("5"), make_shared<PunctuationToken>(")"),
     make_shared<NameToken>("then"),
     make_shared<PunctuationToken>("{") };
    try {
        auto if_parser = make_shared<IfStatementParser>();
        auto condition = if_parser->extractCondition(if_line_valid);
        pair<shared_ptr<Expression>, shared_ptr<Expression>>
            rel_args{ make_shared<Variable>("x"), make_shared<Constant>("5") };
        auto rel = make_shared<RelationalOperation>(">", rel_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> cond_args{ rel, nullptr };
        auto
            expected_condition_expr =
            make_shared<ConditionalOperation>("relationalExpression", cond_args);
        REQUIRE(condition->operator==(*expected_condition_expr));
    }
    catch (std::exception& e) {
    }
}

TEST_CASE("Check if EndOfThenStatements is detected") {
    Tokens end_of_then{
        make_shared<PunctuationToken>("}")
    };
    Tokens else_line_invalid{
        make_shared<NameToken>("else"),
        make_shared<PunctuationToken>("{")
    };
    auto if_parser = make_shared<IfStatementParser>();
    SECTION("Check for validation of syntax of end of then statements") {
        REQUIRE(if_parser->isEndOfStatement(else_line_invalid) == false);
    }SECTION("Check if start of else statement is detected") {
        REQUIRE(if_parser->isEndOfStatement(end_of_then) == true);
    }
}

TEST_CASE("Check if IfStatementParser detects then and else statements") {
    auto prog = make_shared<Program>();
    Tokens tokens
    { make_shared<NameToken>("if"), make_shared<PunctuationToken>("("),
     make_shared<NameToken>("x"), make_shared<RelationalToken>("<"),
     make_shared<IntegerToken>("5"), make_shared<PunctuationToken>(")"),
     make_shared<NameToken>("then"),
     make_shared<PunctuationToken>("{") ,make_shared<NameToken>("x"), make_shared<ArithmeticToken>("="),
     make_shared<NameToken>("y"), make_shared<PunctuationToken>(";") ,make_shared<PunctuationToken>("}") ,make_shared<NameToken>("else"),
        make_shared<PunctuationToken>("{")
   ,make_shared<NameToken>("x"), make_shared<ArithmeticToken>("="),
     make_shared<NameToken>("z"), make_shared<PunctuationToken>(";") , make_shared<PunctuationToken>("}")
    };

    try {
        auto if_parser = make_shared<IfStatementParser>();
        shared_ptr<IfStatement> if_stmt = dynamic_pointer_cast<IfStatement>(if_parser->parseEntity(tokens));
        REQUIRE(if_stmt->getStatementNumber() == 1);
        auto condition = if_stmt->getCondition();
        pair<shared_ptr<Expression>, shared_ptr<Expression>>
            rel_args{ make_shared<Variable>("x"), make_shared<Constant>("5") };
        auto rel = make_shared<RelationalOperation>("<", rel_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> cond_args{ rel, nullptr };
        auto
            expected_condition_expr =
            make_shared<ConditionalOperation>("relationalExpression", cond_args);
        REQUIRE(condition->operator==(*expected_condition_expr));
        auto then_stmts = if_stmt->getThenStatementList();
        REQUIRE(then_stmts[0]->getStatementNumber() == 2);
        auto assign_stmt = dynamic_pointer_cast<AssignStatement>(then_stmts[0]);
        auto print_stmt_wrong = dynamic_pointer_cast<PrintStatement>(then_stmts[0]);
        REQUIRE(assign_stmt != nullptr);
        REQUIRE(print_stmt_wrong == nullptr);
        REQUIRE(assign_stmt->getVariable()->operator==(Variable("x")));
        auto else_stmts = if_stmt->getElseStatementList();
        assign_stmt = dynamic_pointer_cast<AssignStatement>(else_stmts[0]);
        REQUIRE(assign_stmt != nullptr);
        REQUIRE(assign_stmt->getStatementNumber() == 3);
        REQUIRE(*(assign_stmt->getExpression()) == (Variable("z")));
        SUCCEED();
    }
    catch (SpaException& e) {
        cout << e.what() << endl;
        FAIL();
    }
}


TEST_CASE("Check if AssignStatementParser works") {
    Tokens stmt_line
    { make_shared<NameToken>("x"), make_shared<ArithmeticToken>("="),
     make_shared<NameToken>("y"), make_shared<PunctuationToken>(";") };
    auto parser = make_shared<AssignStatementParser>();
    try {
        auto stmt = parser->parseEntity(stmt_line);
    }
    catch (SpaException& e) {
        std::cout << e.what() << std::endl;
        REQUIRE(0);
    }
}

TEST_CASE("Check if Parser works with non control flow statements") {
    Tokens source{ make_shared<NameToken>("procedure"), make_shared<NameToken>("main"),
                           make_shared<PunctuationToken>("{") ,make_shared<NameToken>("x"), make_shared<ArithmeticToken>("="),
     make_shared<NameToken>("y"), make_shared<PunctuationToken>(";") ,make_shared<NameToken>("x"), make_shared<ArithmeticToken>("="),
     make_shared<IntegerToken>("10"), make_shared<PunctuationToken>(";") ,make_shared<NameToken>("read"), make_shared<NameToken>("z"),
                                make_shared<PunctuationToken>(";") ,make_shared<NameToken>("print"), make_shared<NameToken>("x"),
                                 make_shared<PunctuationToken>(";") ,make_shared<PunctuationToken>("}") };
    auto parser = make_shared<Parser>();
    try {
        auto program = parser->parseSource(source);

        SECTION(
            "Check if the AssignStatement has correct fields with Variable expression") {
            auto stmt_var = program->getProcedureList()[0]->getStatementList()[0];
            auto stmt_type = stmt_var->getStatementType();
            auto assign_stmt = dynamic_pointer_cast<AssignStatement>(stmt_var);
            auto var = assign_stmt->getVariable();
            auto expression = assign_stmt->getExpression();
            REQUIRE(assign_stmt->getStatementType() == EntityType::Assign);
            REQUIRE(assign_stmt->getStatementNumber() == 1);
            REQUIRE(var->operator==(Variable("x")));
            REQUIRE(*expression == Variable("y"));
        }

        SECTION(
            "Check if the AssignStatement has correct fields with Constant expression") {
            auto stmt_const = program->getProcedureList()[0]->getStatementList()[1];
            auto assign_stmt = dynamic_pointer_cast<AssignStatement>(stmt_const);
            auto expression = assign_stmt->getExpression();
            REQUIRE(assign_stmt->getStatementType() == EntityType::Assign);
            REQUIRE(assign_stmt->getStatementNumber() == 2);
            REQUIRE(*expression == Constant("10"));
        }

        SECTION("Check if the ReadStatement has correct fields") {
            auto stmt = program->getProcedureList()[0]->getStatementList()[2];
            auto read_stmt = dynamic_pointer_cast<ReadStatement>(stmt);
            auto var = read_stmt->getVariable();
            REQUIRE(read_stmt->getStatementType() == EntityType::Read);
            REQUIRE(read_stmt->getStatementNumber() == 3);
            REQUIRE(*var == Variable("z"));
        }

        SECTION("Check if the PrintStatement has correct fields") {
            auto stmt = program->getProcedureList()[0]->getStatementList()[3];
            auto print_stmt = dynamic_pointer_cast<PrintStatement>(stmt);
            auto var = print_stmt->getVariable();
            REQUIRE(print_stmt->getStatementType() == EntityType::Print);
            REQUIRE(print_stmt->getStatementNumber() == 4);
            REQUIRE(*var == Variable("x"));
        }
    }
    catch (SpaException& e) {
        cout << e.what() << endl;
        REQUIRE(0);
    }
}

TEST_CASE(
    "Check if Parser throws Syntax Error for not starting with a procedure") {
    Tokens invalid_proc_tokens
    { make_shared<NameToken>("x"), make_shared<ArithmeticToken>("="),
     make_shared<NameToken>("y"), make_shared<PunctuationToken>(";") };
    auto parser = make_shared<Parser>();
    try {
        auto program = parser->parseSource(invalid_proc_tokens);
    }
    catch (SyntaxErrorException& e) {
        REQUIRE(e.what() == "A procedure should start with procedure");
    }
}

TEST_CASE("Check if IsEndOFWhileStatement is detected") {
    Tokens while_end_line{
        make_shared<PunctuationToken>("}")
    };
    auto while_parser = make_shared<WhileStatementParser>();
    SECTION("Check if the token is correct for end of while statement") {
        REQUIRE(while_parser->isEndOfWhileStatement(while_end_line) == true);
    }
}

TEST_CASE("Check if WhileStatementParser detects and parses statement list") {
    auto dummy_prog = make_shared<Program>();
    Tokens tokens{
        make_shared<NameToken>("while"), make_shared<PunctuationToken>("("),
        make_shared<NameToken>("x"), make_shared<RelationalToken>("<"),
        make_shared<IntegerToken>("5"), make_shared<PunctuationToken>(")"),
        make_shared<PunctuationToken>("{"),make_shared<NameToken>("x"), make_shared<ArithmeticToken>("="),
     make_shared<NameToken>("y"), make_shared<PunctuationToken>(";") ,make_shared<NameToken>("x"), make_shared<ArithmeticToken>("="),
     make_shared<NameToken>("z"), make_shared<PunctuationToken>(";") ,make_shared<PunctuationToken>("}")
    };

    auto while_parser = make_shared<WhileStatementParser>();
    shared_ptr<WhileStatement> while_stmt = dynamic_pointer_cast<WhileStatement>(while_parser->parseEntity(tokens));
    REQUIRE(while_stmt->getStatementNumber() == 1);
    auto condition = while_stmt->getCondition();
    pair<shared_ptr<Expression>, shared_ptr<Expression>>
        rel_args{ make_shared<Variable>("x"), make_shared<Constant>("5") };
    auto rel = make_shared<RelationalOperation>("<", rel_args);

    pair<shared_ptr<Expression>, shared_ptr<Expression>> cond_args{ rel, nullptr };
    auto
        expected_condition_expr =
        make_shared<ConditionalOperation>("relationalExpression", cond_args);
    REQUIRE(condition->operator==(*expected_condition_expr));
    auto stmt_list = while_stmt->getStatementList();
    REQUIRE(stmt_list[0]->getStatementNumber() == 2);
    auto assign_stmt = dynamic_pointer_cast<AssignStatement>(stmt_list[0]);
    REQUIRE(assign_stmt->getVariable()->operator==(Variable("x")));
    assign_stmt = dynamic_pointer_cast<AssignStatement>(stmt_list[1]);
    REQUIRE(*(assign_stmt->getExpression()) == Variable("z"));
}

TEST_CASE("Check if IntegerToken is parsed as a Constant Expression") {
    Tokens expr_line{ make_shared<IntegerToken>("11") };
    auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
    auto expr = expr_parser->parseEntity(expr_line);
    REQUIRE(expr->getExpressionType() == EntityType::Constant);
}

TEST_CASE("Check if NameToken is parsed as a Variable Expression") {
    Tokens expr_line{ make_shared<NameToken>("x") };
    auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
    auto expr = expr_parser->parseEntity(expr_line);
    REQUIRE(expr->getExpressionType() == EntityType::Variable);
}

TEST_CASE("Check if ArithmeticOperationParser works") {
    SECTION("Check if arithmetic expression with only 2 operands and 1 (+ or -) operator"
        " (e.g., 11 + x) parses correctly") {
        Tokens expr_line
        { make_shared<IntegerToken>("11"), make_shared<ArithmeticToken>("+"), make_shared<NameToken>("x") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        auto actual = expr_parser->parseEntity(expr_line);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
        arguments.first = make_shared<Constant>("11");
        arguments.second = make_shared<Variable>("x");
        shared_ptr<ArithmeticOperation> expected = make_shared<ArithmeticOperation>("+", arguments);
        REQUIRE(actual->operator==(*expected));
    }SECTION(
        "Check if arithmetic expression with only 2 operands and 1 (* or / or %) operator"
        " (e.g., x * z) parses correctly") {
        Tokens expr_line
        { make_shared<NameToken>("x"), make_shared<ArithmeticToken>("*"), make_shared<NameToken>("z") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        auto actual = expr_parser->parseEntity(expr_line);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
        arguments.first = make_shared<Variable>("x");
        arguments.second = make_shared<Variable>("z");
        shared_ptr<ArithmeticOperation> expected = make_shared<ArithmeticOperation>("*", arguments);
        REQUIRE(actual->operator==(*expected));
    }SECTION("Check if arithmetic expression with only 3 operands and 2 (+ or -) operator"
        " (e.g., x + y + z) parses correctly") {
        Tokens expr_line
        { make_shared<NameToken>("x"), make_shared<ArithmeticToken>("+"), make_shared<NameToken>("y"),
         make_shared<ArithmeticToken>("+"), make_shared<NameToken>("z") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        auto actual = expr_parser->parseEntity(expr_line);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> left_subtree_args;
        left_subtree_args.first = make_shared<Variable>("x");
        left_subtree_args.second = make_shared<Variable>("y");
        shared_ptr<ArithmeticOperation> left_subtree = make_shared<ArithmeticOperation>("+", left_subtree_args);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_args;
        root_args.first = left_subtree;
        root_args.second = make_shared<Variable>("z");
        shared_ptr<ArithmeticOperation> root = make_shared<ArithmeticOperation>("+", root_args);
        REQUIRE(actual->operator==(*root));
    }SECTION(
        "Check if arithmetic expression with only 3 operands with 1 (+ or -) first then 1 (* or / or %) operator"
        "(e.g., x + z * 5) parses correctly") {
        Tokens expr_line
        { make_shared<NameToken>("x"), make_shared<ArithmeticToken>("+"), make_shared<NameToken>("z"),
         make_shared<ArithmeticToken>("*"), make_shared<IntegerToken>("5") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        auto actual = expr_parser->parseEntity(expr_line);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> right_subtree_args;
        right_subtree_args.first = make_shared<Variable>("z");
        right_subtree_args.second = make_shared<Constant>("5");
        shared_ptr<ArithmeticOperation> right_subtree = make_shared<ArithmeticOperation>("*", right_subtree_args);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_args;
        root_args.first = make_shared<Variable>("x");
        root_args.second = right_subtree;
        shared_ptr<ArithmeticOperation> root = make_shared<ArithmeticOperation>("+", root_args);
        REQUIRE(actual->operator==(*root));
    }SECTION(
        "Check if arithmetic expression with only 3 operands with 2 (* or / or %) operator "
        "(e.g., x / y * z) parses correctly") {
        Tokens expr_line
        { make_shared<NameToken>("x"), make_shared<ArithmeticToken>("/"), make_shared<NameToken>("y"),
         make_shared<ArithmeticToken>("*"), make_shared<NameToken>("z") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        auto actual = expr_parser->parseEntity(expr_line);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> left_subtree_args;
        left_subtree_args.first = make_shared<Variable>("x");
        left_subtree_args.second = make_shared<Variable>("y");
        shared_ptr<ArithmeticOperation> left_subtree = make_shared<ArithmeticOperation>("/", left_subtree_args);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_args;
        root_args.first = left_subtree;
        root_args.second = make_shared<Variable>("z");
        shared_ptr<ArithmeticOperation> root = make_shared<ArithmeticOperation>("*", root_args);
        REQUIRE(actual->operator==(*root));
    }SECTION(
        "Check if arithmetic expression with only 3 operands with 1 (* or / or %) first then 1 (+ or -) operator"
        "(e.g., z * 5 + x) parses correctly") {
        Tokens expr_line{ make_shared<NameToken>("z"), make_shared<ArithmeticToken>("*"),
                               make_shared<IntegerToken>("5"),
                               make_shared<ArithmeticToken>("+"), make_shared<NameToken>("x") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        auto actual = expr_parser->parseEntity(expr_line);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> left_subtree_args;
        left_subtree_args.first = make_shared<Variable>("z");
        left_subtree_args.second = make_shared<Constant>("5");
        shared_ptr<ArithmeticOperation> left_subtree = make_shared<ArithmeticOperation>("*", left_subtree_args);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_args;
        root_args.first = left_subtree;
        root_args.second = make_shared<Variable>("x");
        shared_ptr<ArithmeticOperation> root = make_shared<ArithmeticOperation>("+", root_args);
        REQUIRE(actual->operator==(*root));
    }SECTION(
        "Check if arithmetic expression with only 3 operands where the 1st pair is enclosed by () and uses 1 (+ or -)"
        "followed by 1 (* or / or %) operator and 1 operand (e.g., (x + z) * 5) parses correctly") {
        Tokens expr_line{ make_shared<PunctuationToken>("("), make_shared<NameToken>("x"),
                               make_shared<ArithmeticToken>("+"),
                               make_shared<NameToken>("z"), make_shared<PunctuationToken>(")"),
                               make_shared<ArithmeticToken>("*"),
                               make_shared<IntegerToken>("5") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        auto actual = expr_parser->parseEntity(expr_line);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> left_subtree_args;
        left_subtree_args.first = make_shared<Variable>("x");
        left_subtree_args.second = make_shared<Variable>("z");
        shared_ptr<ArithmeticOperation> left_subtree = make_shared<ArithmeticOperation>("+", left_subtree_args);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_args;
        root_args.first = left_subtree;
        root_args.second = make_shared<Constant>("5");
        shared_ptr<ArithmeticOperation> root = make_shared<ArithmeticOperation>("*", root_args);
        REQUIRE(actual->operator==(*root));
    }SECTION(
        "Check if arithmetic expression with only > 3 operands using a mixture of operators"
        "and 1 pair enclosed in () (e.g., z % ost + x * (y * z)) parses correctly") {
        Tokens expr_line
        { make_shared<NameToken>("z"), make_shared<ArithmeticToken>("%"), make_shared<NameToken>("ost"),
         make_shared<ArithmeticToken>("+"), make_shared<NameToken>("x"),
         make_shared<ArithmeticToken>("*"),
         make_shared<PunctuationToken>("("), make_shared<NameToken>("y"),
         make_shared<ArithmeticToken>("*"),
         make_shared<NameToken>("z"), make_shared<PunctuationToken>(")") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        auto actual = expr_parser->parseEntity(expr_line);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_left_subtree_args;
        root_left_subtree_args.first = make_shared<Variable>("z");
        root_left_subtree_args.second = make_shared<Variable>("ost");
        shared_ptr<ArithmeticOperation> root_left_subtree = make_shared<ArithmeticOperation>("%", root_left_subtree_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_right_right_subtree_args;
        root_right_right_subtree_args.first = make_shared<Variable>("y");
        root_right_right_subtree_args.second = make_shared<Variable>("z");
        shared_ptr<ArithmeticOperation>
            root_right_right_subtree = make_shared<ArithmeticOperation>("*", root_right_right_subtree_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_right_subtree_args;
        root_right_subtree_args.first = make_shared<Variable>("x");
        root_right_subtree_args.second = root_right_right_subtree;
        shared_ptr<ArithmeticOperation> root_right_subtree = make_shared<ArithmeticOperation>("*", root_right_subtree_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_args;
        root_args.first = root_left_subtree;
        root_args.second = root_right_subtree;
        shared_ptr<ArithmeticOperation> root = make_shared<ArithmeticOperation>("+", root_args);
        REQUIRE(actual->operator==(*root));
    }SECTION(
        "Check if complex arithmetic expression "
        "[e.g., (((24 + 25) * 26 ) + 27) -  (28 + ( 29 / (30 + 31))] parses correctly ") {
        Tokens expr_line
        { make_shared<PunctuationToken>("("), make_shared<PunctuationToken>("("),
         make_shared<PunctuationToken>("("), make_shared<IntegerToken>("24"),
         make_shared<ArithmeticToken>("+"), make_shared<IntegerToken>("25"),
         make_shared<PunctuationToken>(")"), make_shared<ArithmeticToken>("*"),
         make_shared<IntegerToken>("26"), make_shared<PunctuationToken>(")"),
         make_shared<ArithmeticToken>("+"), make_shared<IntegerToken>("27"),
         make_shared<PunctuationToken>(")"), make_shared<ArithmeticToken>("-"),
         make_shared<PunctuationToken>("("), make_shared<IntegerToken>("28"),
         make_shared<ArithmeticToken>("+"), make_shared<IntegerToken>("29"),
         make_shared<ArithmeticToken>("/"), make_shared<PunctuationToken>("("),
         make_shared<IntegerToken>("30"), make_shared<ArithmeticToken>("+"),
         make_shared<IntegerToken>("31"), make_shared<PunctuationToken>(")"),
         make_shared<PunctuationToken>(")") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        auto actual = expr_parser->parseEntity(expr_line);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> t1_args;
        t1_args.first = make_shared<Constant>("24");
        t1_args.second = make_shared<Constant>("25");
        shared_ptr<ArithmeticOperation> t1 = make_shared<ArithmeticOperation>("+", t1_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> t2_args;
        t2_args.first = t1;
        t2_args.second = make_shared<Constant>("26");
        shared_ptr<ArithmeticOperation>
            t2 = make_shared<ArithmeticOperation>("*", t2_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> t3_args;
        t3_args.first = t2;
        t3_args.second = make_shared<Constant>("27");
        shared_ptr<ArithmeticOperation> t3 = make_shared<ArithmeticOperation>("+", t3_args);

        // (28 + ( 29 / (30 + 31))
        pair<shared_ptr<Expression>, shared_ptr<Expression>> t4_args;
        t4_args.first = make_shared<Constant>("30");
        t4_args.second = make_shared<Constant>("31");
        shared_ptr<ArithmeticOperation> t4 = make_shared<ArithmeticOperation>("+", t4_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> t5_args;
        t5_args.first = make_shared<Constant>("29");
        t5_args.second = t4;
        shared_ptr<ArithmeticOperation> t5 = make_shared<ArithmeticOperation>("/", t5_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> t6_args;
        t6_args.first = make_shared<Constant>("28");
        t6_args.second = t5;
        shared_ptr<ArithmeticOperation> t6 = make_shared<ArithmeticOperation>("+", t6_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_args;
        root_args.first = t3;
        root_args.second = t6;
        shared_ptr<ArithmeticOperation> root = make_shared<ArithmeticOperation>("-", root_args);
        REQUIRE(actual->operator==(*root));
    }SECTION("Check if arithmetic expression with unbalanced () [e.g. 2 * (x + 1 ] throws Syntax error") {
        Tokens expr_line{ make_shared<IntegerToken>("2"), make_shared<ArithmeticToken>("*"),
                               make_shared<PunctuationToken>("("),
                               make_shared<NameToken>("x"), make_shared<ArithmeticToken>("+"),
                               make_shared<IntegerToken>("1") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        REQUIRE_THROWS_AS(expr_parser->parseEntity(expr_line), SyntaxErrorException);
    }SECTION("Check if arithmetic expression with unbalanced () [e.g. 2 * x) + 1 ] throws Syntax error") {
        Tokens expr_line{ make_shared<IntegerToken>("2"), make_shared<ArithmeticToken>("*"),
                               make_shared<NameToken>("x"),
                               make_shared<PunctuationToken>(")"),
                               make_shared<ArithmeticToken>("+"), make_shared<IntegerToken>("1") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        REQUIRE_THROWS_AS(expr_parser->parseEntity(expr_line), SyntaxErrorException);
    }SECTION("Check if arithmetic expression with unbalanced () [e.g. (2 * x) + 1) ] throws Syntax error") {
        Tokens expr_line{ make_shared<PunctuationToken>("("), make_shared<IntegerToken>("2"),
                               make_shared<ArithmeticToken>("*"),
                               make_shared<NameToken>("x"), make_shared<PunctuationToken>(")"),
                               make_shared<ArithmeticToken>("+"),
                               make_shared<IntegerToken>("1"), make_shared<PunctuationToken>(")") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        REQUIRE_THROWS_AS(expr_parser->parseEntity(expr_line), SyntaxErrorException);
    }SECTION("Check if arithmetic expression with unbalanced () [e.g. ((2+x) ] throws Syntax error") {
        Tokens expr_line
        { make_shared<PunctuationToken>("("), make_shared<PunctuationToken>("("),
         make_shared<IntegerToken>("2"),
         make_shared<ArithmeticToken>("+"), make_shared<NameToken>("x"),
         make_shared<PunctuationToken>(")") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::Assign);
        REQUIRE_THROWS_AS(expr_parser->parseEntity(expr_line), SyntaxErrorException);
    }
}

TEST_CASE("Check if ConditionalOperationParser & RelationalOperationParser works") {
    SECTION("Check if relationalExpression (e.g. x == 1) parses correctly") {
        Tokens expr_line{ make_shared<NameToken>("x"), make_shared<RelationalToken>("=="),
                               make_shared<IntegerToken>("1") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::If);
        auto actual = expr_parser->parseEntity(expr_line);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> rel_args;
        rel_args.first = make_shared<Variable>("x");
        rel_args.second = make_shared<Constant>("1");
        shared_ptr<RelationalOperation> rel = make_shared<RelationalOperation>("==", rel_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> cond_args;
        cond_args.first = rel;
        shared_ptr<ConditionalOperation> expected = make_shared<ConditionalOperation>("relationalExpression", cond_args);
        REQUIRE(actual->operator==(*expected));
    }SECTION("Check if relationalExpression with missing rel_op (e.g. x y) throws syntax error") {
        Tokens expr_line{ make_shared<NameToken>("x"), make_shared<NameToken>("y") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::If);
        REQUIRE_THROWS_AS(expr_parser->parseEntity(expr_line), SyntaxErrorException);
    }SECTION("Check if relationalExpression with missing RHS rel_factor (e.g. x != ) throws syntax error") {
        Tokens expr_line{ make_shared<NameToken>("x"), make_shared<RelationalToken>("!=") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::If);
        REQUIRE_THROWS_AS(expr_parser->parseEntity(expr_line), SyntaxErrorException);
    }SECTION("Check if ! '(' cond_expr ')' (e.g. ! (x > y) ) parses correctly") {
        Tokens expr_line
        { make_shared<ConditionalToken>("!"), make_shared<PunctuationToken>("("),
         make_shared<NameToken>("x"),
         make_shared<RelationalToken>(">"), make_shared<NameToken>("y"),
         make_shared<PunctuationToken>(")") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::While);
        auto actual = expr_parser->parseEntity(expr_line);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> rel_args;
        rel_args.first = make_shared<Variable>("x");
        rel_args.second = make_shared<Variable>("y");
        shared_ptr<RelationalOperation> rel = make_shared<RelationalOperation>(">", rel_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> inner_cond_args;
        inner_cond_args.first = rel;
        shared_ptr<ConditionalOperation> inner_cond_expr = make_shared<ConditionalOperation>("relationalExpression", inner_cond_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_cond_args;
        root_cond_args.first = inner_cond_expr;
        shared_ptr<ConditionalOperation> root_cond_expr = make_shared<ConditionalOperation>("!", root_cond_args);
        REQUIRE(actual->operator==(*root_cond_expr));
    }SECTION("Check if '(' cond_expr ')' '&&' or '||' '(' cond_expr ')' (e.g. (x < y) || (y >= 100) ) parses correctly") {
        Tokens expr_line{ make_shared<PunctuationToken>("("), make_shared<NameToken>("x"),
                               make_shared<RelationalToken>("<"),
                               make_shared<NameToken>("y"), make_shared<PunctuationToken>(")"),
                               make_shared<ConditionalToken>("||"),
                               make_shared<PunctuationToken>("("), make_shared<NameToken>("y"),
                               make_shared<RelationalToken>(">="),
                               make_shared<IntegerToken>("100"), make_shared<PunctuationToken>(")") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::If);
        auto actual = expr_parser->parseEntity(expr_line);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> lhs_rel_args;
        lhs_rel_args.first = make_shared<Variable>("x");
        lhs_rel_args.second = make_shared<Variable>("y");
        shared_ptr<RelationalOperation> lhs_relationalExpression = make_shared<RelationalOperation>("<", lhs_rel_args);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> lhs_cond_args;
        lhs_cond_args.first = lhs_relationalExpression;
        shared_ptr<ConditionalOperation> lhs_cond_expr = make_shared<ConditionalOperation>("relationalExpression", lhs_cond_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> rhs_rel_args;
        rhs_rel_args.first = make_shared<Variable>("y");
        rhs_rel_args.second = make_shared<Constant>("100");
        shared_ptr<RelationalOperation> rhs_relationalExpression = make_shared<RelationalOperation>(">=", rhs_rel_args);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> rhs_cond_args;
        rhs_cond_args.first = rhs_relationalExpression;
        shared_ptr<ConditionalOperation> rhs_cond_expr = make_shared<ConditionalOperation>("relationalExpression", rhs_cond_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_cond_args;
        root_cond_args.first = lhs_cond_expr;
        root_cond_args.second = rhs_cond_expr;
        shared_ptr<ConditionalOperation> root_cond_expr = make_shared<ConditionalOperation>("||", root_cond_args);
        REQUIRE(actual->operator==(*root_cond_expr));
    }SECTION("Check if '(' cond_expr ') '&&' or '||' '(' cond_expr ')' [e.g. (!(x!=1)) && (!(x==1))] parses correctly") {
        Tokens
            expr_line{ make_shared<PunctuationToken>("("), make_shared<ConditionalToken>("!"),
                      make_shared<PunctuationToken>("("), make_shared<NameToken>("x"),
                      make_shared<RelationalToken>("!="), make_shared<IntegerToken>("1"),
                      make_shared<PunctuationToken>(")"),
                      make_shared<PunctuationToken>(")"),
                      make_shared<ConditionalToken>("&&"),
                      make_shared<PunctuationToken>("("),
                      make_shared<ConditionalToken>("!"), make_shared<PunctuationToken>("("),
                      make_shared<NameToken>("x"), make_shared<RelationalToken>("=="),
                      make_shared<IntegerToken>("1"), make_shared<PunctuationToken>(")"),
                      make_shared<PunctuationToken>(")")
        };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::If);
        auto actual = expr_parser->parseEntity(expr_line);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> lhs_nested_cond_rel_args;
        lhs_nested_cond_rel_args.first = make_shared<Variable>("x");
        lhs_nested_cond_rel_args.second = make_shared<Constant>("1");
        shared_ptr<RelationalOperation> rel = make_shared<RelationalOperation>("!=", lhs_nested_cond_rel_args);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> lhs_nested_cond_args;
        lhs_nested_cond_args.first = rel;
        shared_ptr<ConditionalOperation>
            lhs_nested_cond_expr = make_shared<ConditionalOperation>("relationalExpression", lhs_nested_cond_args);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> lhs_root_cond_args;
        lhs_root_cond_args.first = lhs_nested_cond_expr;
        shared_ptr<ConditionalOperation> lhs_root_cond_expr = make_shared<ConditionalOperation>("!", lhs_root_cond_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> rhs_nested_cond_rel_args;
        rhs_nested_cond_rel_args.first = make_shared<Variable>("x");
        rhs_nested_cond_rel_args.second = make_shared<Constant>("1");
        rel = make_shared<RelationalOperation>("==", rhs_nested_cond_rel_args);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> rhs_nested_cond_args;
        rhs_nested_cond_args.first = rel;
        shared_ptr<ConditionalOperation>
            rhs_nested_cond_expr = make_shared<ConditionalOperation>("relationalExpression", rhs_nested_cond_args);
        pair<shared_ptr<Expression>, shared_ptr<Expression>> rhs_root_cond_args;
        rhs_root_cond_args.first = rhs_nested_cond_expr;
        shared_ptr<ConditionalOperation> rhs_root_cond_expr = make_shared<ConditionalOperation>("!", rhs_root_cond_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> root_cond_args;
        root_cond_args.first = lhs_root_cond_expr;
        root_cond_args.second = rhs_root_cond_expr;
        shared_ptr<ConditionalOperation> root_cond_expr = make_shared<ConditionalOperation>("&&", root_cond_args);
        REQUIRE(actual->operator==(*root_cond_expr));
    }SECTION("Check if cond_expr with rel_factor (var_name) 'any rel_op' rel_factor (expr)"
        "(e.g. x > 1 + 2) parses correctly") {
        Tokens expr_line{ make_shared<NameToken>("x"), make_shared<RelationalToken>(">"),
                               make_shared<IntegerToken>("1"), make_shared<ArithmeticToken>("+"),
                               make_shared<IntegerToken>("2") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::While);
        auto actual = expr_parser->parseEntity(expr_line);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> expr_args;
        expr_args.first = make_shared<Constant>("1");
        expr_args.second = make_shared<Constant>("2");
        shared_ptr<ArithmeticOperation> expr = make_shared<ArithmeticOperation>("+", expr_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> rel_args;
        rel_args.first = make_shared<Variable>("x");
        rel_args.second = expr;
        shared_ptr<RelationalOperation> relationalExpression = make_shared<RelationalOperation>(">", rel_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> cond_expr_args;
        cond_expr_args.first = relationalExpression;
        shared_ptr<ConditionalOperation> root_cond_expr = make_shared<ConditionalOperation>("relationalExpression", cond_expr_args);
        REQUIRE(actual->operator==(*root_cond_expr));
    }SECTION(
        "Check if relationalExpression with complex arithmetic expression "
        "[e.g., (((24 + 25) * 26 ) + 27) - (28 + ( 29 / (30 + 31))) > 0] parses correctly ") {
        Tokens expr_line
        { make_shared<PunctuationToken>("("), make_shared<PunctuationToken>("("),
         make_shared<PunctuationToken>("("), make_shared<IntegerToken>("24"),
         make_shared<ArithmeticToken>("+"), make_shared<IntegerToken>("25"),
         make_shared<PunctuationToken>(")"), make_shared<ArithmeticToken>("*"),
         make_shared<IntegerToken>("26"), make_shared<PunctuationToken>(")"),
         make_shared<ArithmeticToken>("+"), make_shared<IntegerToken>("27"),
         make_shared<PunctuationToken>(")"), make_shared<ArithmeticToken>("-"),
         make_shared<PunctuationToken>("("), make_shared<IntegerToken>("28"),
         make_shared<ArithmeticToken>("+"), make_shared<PunctuationToken>("("),
         make_shared<IntegerToken>("29"), make_shared<ArithmeticToken>("/"),
         make_shared<PunctuationToken>("("), make_shared<IntegerToken>("30"),
         make_shared<ArithmeticToken>("+"), make_shared<IntegerToken>("31"),
         make_shared<PunctuationToken>(")"), make_shared<PunctuationToken>(")"),
         make_shared<PunctuationToken>(")"),
         make_shared<RelationalToken>(">"), make_shared<IntegerToken>("0") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::If);
        auto actual = expr_parser->parseEntity(expr_line);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> arithmetic_t1_args;
        arithmetic_t1_args.first = make_shared<Constant>("24");
        arithmetic_t1_args.second = make_shared<Constant>("25");
        shared_ptr<ArithmeticOperation> arithmetic_t1 = make_shared<ArithmeticOperation>("+", arithmetic_t1_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> arithmetic_t2_args;
        arithmetic_t2_args.first = arithmetic_t1;
        arithmetic_t2_args.second = make_shared<Constant>("26");
        shared_ptr<ArithmeticOperation>
            arithmetic_t2 = make_shared<ArithmeticOperation>("*", arithmetic_t2_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> arithmetic_t3_args;
        arithmetic_t3_args.first = arithmetic_t2;
        arithmetic_t3_args.second = make_shared<Constant>("27");
        shared_ptr<ArithmeticOperation> arithmetic_t3 = make_shared<ArithmeticOperation>("+", arithmetic_t3_args);

        // (28 + ( 29 / (30 + 31))
        pair<shared_ptr<Expression>, shared_ptr<Expression>> arithmetic_t4_args;
        arithmetic_t4_args.first = make_shared<Constant>("30");
        arithmetic_t4_args.second = make_shared<Constant>("31");
        shared_ptr<ArithmeticOperation> arithmetic_t4 = make_shared<ArithmeticOperation>("+", arithmetic_t4_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> arithmetic_t5_args;
        arithmetic_t5_args.first = make_shared<Constant>("29");
        arithmetic_t5_args.second = arithmetic_t4;
        shared_ptr<ArithmeticOperation> arithmetic_t5 = make_shared<ArithmeticOperation>("/", arithmetic_t5_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> arithmetic_t6_args;
        arithmetic_t6_args.first = make_shared<Constant>("28");
        arithmetic_t6_args.second = arithmetic_t5;
        shared_ptr<ArithmeticOperation> arithmetic_t6 = make_shared<ArithmeticOperation>("+", arithmetic_t6_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> arithmetic_root_args;
        arithmetic_root_args.first = arithmetic_t3;
        arithmetic_root_args.second = arithmetic_t6;
        shared_ptr<ArithmeticOperation> arithmetic_root = make_shared<ArithmeticOperation>("-", arithmetic_root_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> relational_root_args;
        relational_root_args.first = arithmetic_root;
        relational_root_args.second = make_shared<Constant>("0");
        shared_ptr<RelationalOperation> relational_root = make_shared<RelationalOperation>(">", relational_root_args);

        pair<shared_ptr<Expression>, shared_ptr<Expression>> conditional_root_args;
        conditional_root_args.first = relational_root;
        shared_ptr<ConditionalOperation> conditional_root = make_shared<ConditionalOperation>("relationalExpression",
            conditional_root_args);
        REQUIRE(actual->operator==(*conditional_root));
    }SECTION("Check if cond_expr with missing RHS cond_expr [e.g. (x < y) && ] throws syntax error") {
        Tokens expr_line{ make_shared<PunctuationToken>("("), make_shared<NameToken>("x"),
                               make_shared<RelationalToken>("<"),
                               make_shared<NameToken>("y"), make_shared<PunctuationToken>(")"),
                               make_shared<ConditionalToken>("&&") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::If);
        REQUIRE_THROWS_AS(expr_parser->parseEntity(expr_line), SyntaxErrorException);
    }SECTION("Check if cond_expr with unbalanced () [e.g. (x < y) && (z <= 100))] throws syntax error") {
        Tokens expr_line{ make_shared<PunctuationToken>("("), make_shared<NameToken>("x"),
                               make_shared<RelationalToken>("<"),
                               make_shared<NameToken>("y"), make_shared<PunctuationToken>(")"),
                               make_shared<ConditionalToken>("&&"),
                               make_shared<PunctuationToken>("("), make_shared<NameToken>("z"),
                               make_shared<RelationalToken>("<="),
                               make_shared<IntegerToken>("100"), make_shared<PunctuationToken>(")"),
                               make_shared<PunctuationToken>(")") };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::If);
        auto expr = expr_parser->parseEntity(expr_line);
        REQUIRE_THROWS_AS(expr_parser->parseEntity(expr_line), SyntaxErrorException);
    }
    SECTION("Check if cond_expr [  ( ! (a != 0) ) && (0 > 1) ] parses without syntax error") {
        Tokens expr_line{
            make_shared<PunctuationToken>("("), make_shared<ConditionalToken>("!"),
            make_shared<PunctuationToken>("("), make_shared<NameToken>("a"),
            make_shared<RelationalToken>("!="), make_shared<IntegerToken>("0"),
            make_shared<PunctuationToken>(")"), make_shared<PunctuationToken>(")"),
            make_shared<ConditionalToken>("&&"), make_shared<PunctuationToken>("("),
            make_shared<IntegerToken>("0"), make_shared<RelationalToken>(">"),
            make_shared<IntegerToken>("1"), make_shared<PunctuationToken>(")"),
            make_shared<PunctuationToken>(")")
        };
        auto expr_parser = ExpressionParserFactory::getExpressionParser(expr_line, EntityType::If);
        REQUIRE_NOTHROW(expr_parser->parseEntity(expr_line));
    }
}