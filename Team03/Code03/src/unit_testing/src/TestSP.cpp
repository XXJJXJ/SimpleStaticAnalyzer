#include <stdlib.h> 
#include <unordered_map>
#include "catch.hpp"
#include "sp/parser/Parser.h"
#include "sp/parser/ProcedureParser.h"
#include "sp/parser/CallStatementParser.h"
#include "sp/parser/AssignStatementParser.h"
#include "sp/parser/WhileStatementParser.h"
#include "sp/parser/VariableParser.h"
#include "sp/tokenizer/Token/NameToken.h"
#include "sp/tokenizer/Token/PunctuationToken.h"
#include "sp/tokenizer/Token/IntegerToken.h"
#include "sp/tokenizer/TokenFactory/ConditionalTokenFactory.h"
#include "sp/tokenizer/TokenFactory/RelationalTokenFactory.h"
#include "sp/tokenizer/Tokenizer.h"

TEST_CASE("1st SP Unit Test: Parser no procedure") {
    try {
        Tokens tokens = {};
        Parser parser = Parser();
        parser.parseSource(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Program should have at least 1 procedure");
    }
}

TEST_CASE("2nd SP Unit Test: Parser with procedure") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("procedure"),
            make_shared<NameToken>("test"),
            make_shared<PunctuationToken>("{"),
            make_shared<NameToken>("x"),
            make_shared<ArithmeticToken>("="),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(";"),
            make_shared<PunctuationToken>("}")
        };
        Parser parser = Parser();
        parser.parseSource(tokens);
        SUCCEED();
    }
    catch (SpaException& e) {
        FAIL();
    }
}

TEST_CASE("3rd SP Unit Test: Procedure Parser with no statements") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("procedure"),
            make_shared<NameToken>("test"),
            make_shared<PunctuationToken>("{"),
            make_shared<PunctuationToken>("}")
        };
        ProcedureParser procedureParser = ProcedureParser();
        procedureParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Empty Procedure");
    }
}

TEST_CASE("4th SP Unit Test: Procedure Parser with no } token") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("procedure"),
            make_shared<NameToken>("test"),
            make_shared<PunctuationToken>("{"),
            make_shared<NameToken>("x"),
            make_shared<ArithmeticToken>("="),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(";")
        };
        ProcedureParser procedureParser = ProcedureParser();
        procedureParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing } token in Procedure");
    }
}

TEST_CASE("5th SP Unit Test: Procedure Parser with no procedure name token") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("test"),
            make_shared<PunctuationToken>("{"),
            make_shared<NameToken>("x"),
            make_shared<ArithmeticToken>("="),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(";"),
            make_shared<PunctuationToken>("}")
        };
        ProcedureParser procedureParser = ProcedureParser();
        procedureParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing procedure name token");
    }
}

TEST_CASE("6th SP Unit Test: Procedure Parser with no name token") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("procedure"),
            make_shared<PunctuationToken>("{"),
            make_shared<NameToken>("x"),
            make_shared<ArithmeticToken>("="),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(";"),
            make_shared<PunctuationToken>("}")
        };
        ProcedureParser procedureParser = ProcedureParser();
        procedureParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing name token");
    }
}

TEST_CASE("7th SP Unit Test: Procedure Parser with no { token") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("procedure"),
            make_shared<NameToken>("test"),
            make_shared<NameToken>("x"),
            make_shared<ArithmeticToken>("="),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(";"),
            make_shared<PunctuationToken>("}")
        };
        ProcedureParser procedureParser = ProcedureParser();
        procedureParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing { token in Procedure");
    }
}

TEST_CASE("8th SP Unit Test: While Statement Parser with empty while statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("while"),
            make_shared<PunctuationToken>("("),
            make_shared<NameToken>("x"),
            make_shared<RelationalToken>(">"),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(")"),
            make_shared<PunctuationToken>("{"),
            make_shared<PunctuationToken>("}"),
        };
        WhileStatementParser procedureParser = WhileStatementParser();
        procedureParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Empty While statement");
    }
}

TEST_CASE("9th SP Unit Test: While Statement Parser with no } token") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("while"),
            make_shared<PunctuationToken>("("),
            make_shared<NameToken>("x"),
            make_shared<RelationalToken>(">"),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(")"),
            make_shared<PunctuationToken>("{"),
            make_shared<NameToken>("x"),
            make_shared<ArithmeticToken>("="),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(";")
        };
        WhileStatementParser procedureParser = WhileStatementParser();
        procedureParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing } token in While statement");
    }
}

TEST_CASE("10th SP Unit Test: While Statement Parser with no { token") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("while"),
            make_shared<PunctuationToken>("("),
            make_shared<NameToken>("x"),
            make_shared<RelationalToken>(">"),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(")"),
            make_shared<NameToken>("x"),
            make_shared<RelationalToken>("="),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(";"),
            make_shared<PunctuationToken>("}")
        };
        WhileStatementParser procedureParser = WhileStatementParser();
        procedureParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing { token in While statement");
    }
}

TEST_CASE("11th SP Unit Test: While Statement Parser with no ( token") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("while"),
            make_shared<NameToken>("x"),
            make_shared<RelationalToken>(">"),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(")"),
            make_shared<PunctuationToken>("{"),
            make_shared<NameToken>("x"),
            make_shared<RelationalToken>("="),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(";"),
            make_shared<PunctuationToken>("}"),
        };
        WhileStatementParser procedureParser = WhileStatementParser();
        procedureParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing ( token in While statement");
    }
}

TEST_CASE("12th SP Unit Test: While Statement Parser with no ) token") {
    try {
        std::string simple_string = "procedure test {while(x>2{x=5;}}";
        Tokens tokens = {
            make_shared<NameToken>("while"),
            make_shared<PunctuationToken>("("),
            make_shared<NameToken>("x"),
            make_shared<RelationalToken>(">"),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>("{"),
            make_shared<NameToken>("x"),
            make_shared<RelationalToken>("="),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(";"),
            make_shared<PunctuationToken>("}"),
        };
        WhileStatementParser procedureParser = WhileStatementParser();
        procedureParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing ) token in While statement");
    }
}

TEST_CASE("13th SP Unit Test: Variable Parser invalid token") {
    try {
        Tokens tokens = {make_shared<NameToken>("2")};
        VariableParser variableParser = VariableParser();
        variableParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Invalid Variable");
    }
}

TEST_CASE("14th SP Unit Test: StatementParserFactory Insufficient number of tokens") {
    try {
        Tokens tokens = {make_shared<NameToken>("2")};
        StatementParserFactory statementParserFactory = StatementParserFactory();
        statementParserFactory.getStatementParser(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Insufficient number of tokens");
    }
}

TEST_CASE("15th SP Unit Test: StatementParserFactory Unknown Statement Type") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("2"),
            make_shared<NameToken>("2"),
            make_shared<NameToken>("2")
        };
        StatementParserFactory statementParserFactory = StatementParserFactory();
        statementParserFactory.getStatementParser(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Unknown Statement Type");
    }
}

TEST_CASE("16th SP Unit Test: ReadStatementParser Missing read name token in Read statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("dsad"),
            make_shared<NameToken>("x"),
            make_shared<PunctuationToken>(";")
        };
        ReadStatementParser readStatementParser = ReadStatementParser();
        readStatementParser.extractVariableName(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing read name token in Read statement");
    }
}

TEST_CASE("17th SP Unit Test: ReadStatementParser Missing variable name token in Read statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("read"),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(";")
        };
        ReadStatementParser readStatementParser = ReadStatementParser();
        readStatementParser.extractVariableName(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing variable name token in Read statement");
    }
}

TEST_CASE("18th SP Unit Test: ReadStatementParser Missing ; token in Read statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("read"),
            make_shared<NameToken>("test"),
            make_shared<PunctuationToken>(")")
        };
        ReadStatementParser readStatementParser = ReadStatementParser();
        readStatementParser.extractVariableName(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing ; token in Read statement");
    }
}

TEST_CASE("19th SP Unit Test: PrintStatementParser Missing print name token in Print statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("dsad"),
            make_shared<NameToken>("test"),
            make_shared<PunctuationToken>(";")
        };
        PrintStatementParser printStatementParser = PrintStatementParser();
        printStatementParser.extractVariableName(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing print name token in Print statement");
    }
}

TEST_CASE("20th SP Unit Test: PrintStatementParser Missing variable name token in Print statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("print"),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(";")
        };
        PrintStatementParser printStatementParser = PrintStatementParser();
        printStatementParser.extractVariableName(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing variable name token in Print statement");
    }
}

TEST_CASE("21st SP Unit Test: PrintStatementParser Missing ; token in Print statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("print"),
            make_shared<NameToken>("test"),
            make_shared<PunctuationToken>(")")
        };
        PrintStatementParser printStatementParser = PrintStatementParser();
        printStatementParser.extractVariableName(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing ; token in Print statement");
    }
}

TEST_CASE("22nd SP Unit Test: IfStatementParser Missing if name token in If statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("print"),
            make_shared<NameToken>("test")
        };
        IfStatementParser ifStatementParser = IfStatementParser();
        ifStatementParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing if name token in If statement");
    }
}

TEST_CASE("23rd SP Unit Test: IfStatementParser Missing ( token in If statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("if"),
            make_shared<NameToken>("test")
        };
        IfStatementParser ifStatementParser = IfStatementParser();
        ifStatementParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing ( token in If statement");
    }
}

TEST_CASE("24th SP Unit Test: IfStatementParser Missing { token in If statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("if"),
            make_shared<PunctuationToken>("("),
            make_shared<NameToken>("x"),
            make_shared<RelationalToken>(">"),
            make_shared<IntegerToken>("5"),
            make_shared<PunctuationToken>(")")
        };
        IfStatementParser ifStatementParser = IfStatementParser();
        ifStatementParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing { token in If statement");
    }
}

TEST_CASE("25th SP Unit Test: IfStatementParser Missing ) token in If statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("if"),
            make_shared<PunctuationToken>("("),
            make_shared<NameToken>("x"),
            make_shared<RelationalToken>(">"),
            make_shared<IntegerToken>("5"),
            make_shared<PunctuationToken>("{"),
        };
        IfStatementParser ifStatementParser = IfStatementParser();
        ifStatementParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing ) token in If statement");
    }
}

TEST_CASE("26th SP Unit Test: IfStatementParser Missing then name token in If statement's then block") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("if"),
            make_shared<PunctuationToken>("("),
            make_shared<NameToken>("x"),
            make_shared<RelationalToken>(">"),
            make_shared<IntegerToken>("5"),
            make_shared<PunctuationToken>(")"),
            make_shared<NameToken>("blah"),
            make_shared<PunctuationToken>("{")
        };
        IfStatementParser ifStatementParser = IfStatementParser();
        ifStatementParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing then name token in If statement's then block");
    }
}

TEST_CASE("27th SP Unit Test: ConstantParser Invalid Constant") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("5"),
        };
        ConstantParser constantParser = ConstantParser();
        constantParser.parseEntity(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Invalid Constant");
    }
}

TEST_CASE("28th SP Unit Test: CallStatementParser Missing call name token in Call statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("dsad"),
            make_shared<NameToken>("test"),
            make_shared<PunctuationToken>(";")
        };
        CallStatementParser callStatementParser = CallStatementParser();
        callStatementParser.extractProcedureName(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing call name token in Call statement");
    }
}

TEST_CASE("29th SP Unit Test: CallStatementParser Missing name token in Call statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("call"),
            make_shared<IntegerToken>("2"),
            make_shared<PunctuationToken>(";")
        };
        CallStatementParser callStatementParser = CallStatementParser();
        callStatementParser.extractProcedureName(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing name token in Call statement");
    }
}

TEST_CASE("30th SP Unit Test: CallStatementParser Missing ; token in Call statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("call"),
            make_shared<NameToken>("test"),
            make_shared<PunctuationToken>(")")
        };
        CallStatementParser callStatementParser = CallStatementParser();
        callStatementParser.extractProcedureName(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing ; token in Call statement");
    }
}

TEST_CASE("31st SP Unit Test: AssignStatementParser Missing variable name token in Assign statement") {
    try {
        Tokens tokens = {
            make_shared<IntegerToken>("1"),
            make_shared<NameToken>("test"),
        };
        AssignStatementParser assignStatementParser = AssignStatementParser();
        assignStatementParser.extractVariableName(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing variable name token in Assign statement");
    }
}

TEST_CASE("32nd SP Unit Test: AssignStatementParser Missing = token in Assign statement") {
    try {
        Tokens tokens = {
            make_shared<NameToken>("x"),
            make_shared<ArithmeticToken>(";"),
        };
        AssignStatementParser assignStatementParser = AssignStatementParser();
        assignStatementParser.extractVariableName(tokens);
    }
    catch (SpaException& e) {
        REQUIRE(e.what() == "Missing = token in Assign statement");
    }
}

TEST_CASE("33rd SP Unit Test: Test ConditionalTokenFactory") {
    try {
        shared_ptr<Token> token = ConditionalTokenFactory::createToken("&&");
        REQUIRE(token->getValue() == "&&");
        shared_ptr<Token> token2 = ConditionalTokenFactory::createToken("||");
        REQUIRE(token2->getValue() == "||");
    }
    catch (SpaException& e) {
        FAIL();
    }
}

TEST_CASE("34th SP Unit Test: Test RelationalTokenFactory") {
    try {
        shared_ptr<Token> token = RelationalTokenFactory::createToken(">");
        REQUIRE(token->getValue() == ">");
        shared_ptr<Token> token2 = RelationalTokenFactory::createToken("<");
        REQUIRE(token2->getValue() == "<");
        shared_ptr<Token> token3 = RelationalTokenFactory::createToken("==");
        REQUIRE(token3->getValue() == "==");
    }
    catch (SpaException& e) {
        FAIL();
    }
}

TEST_CASE("35th SP Unit Test: Test Tokenizer stringToToken on all possibilities") {
    try {
        Tokenizer tokenizer = Tokenizer();
        shared_ptr<Token> token = tokenizer.stringToToken("(");
        REQUIRE(token->getValue() == "(");
        shared_ptr<Token> token2 = tokenizer.stringToToken(")");
        REQUIRE(token2->getValue() == ")");
        shared_ptr<Token> token3 = tokenizer.stringToToken("{");
        REQUIRE(token3->getValue() == "{");
        shared_ptr<Token> token4 = tokenizer.stringToToken("}");
        REQUIRE(token4->getValue() == "}");
        shared_ptr<Token> token5 = tokenizer.stringToToken(";");
        REQUIRE(token5->getValue() == ";");
        shared_ptr<Token> token6 = tokenizer.stringToToken("\"");
        REQUIRE(token6->getValue() == "\"");
        shared_ptr<Token> token7 = tokenizer.stringToToken("<");
        REQUIRE(token7->getValue() == "<");
        shared_ptr<Token> token8 = tokenizer.stringToToken("&&");
        REQUIRE(token8->getValue() == "&&");
        REQUIRE_THROWS(tokenizer.stringToToken("inv@lid"));
        REQUIRE_THROWS(tokenizer.stringToToken("2ABC"));
    }
    catch (SpaException& e) {
        FAIL();
    }
}

TEST_CASE("36th SP Unit Test: Test Tokenizer tokenize") {
    try {
        Tokenizer tokenizer = Tokenizer();
        ifstream file("non_existent_file.txt");
        Tokens tokens = tokenizer.tokenize(file);
        REQUIRE(tokens.size() == 0);
    }
    catch (SpaException& e) {
        FAIL();
    }
}