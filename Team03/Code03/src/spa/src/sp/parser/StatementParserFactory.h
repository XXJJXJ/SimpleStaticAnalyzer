#pragma once

#include<deque>
#include<vector>
#include "StatementParser.h"
#include "PrintStatementParser.h"
#include "ReadStatementParser.h"
#include "IfStatementParser.h"
#include "WhileStatementParser.h"
#include "AssignStatementParser.h"

class StatementParserFactory {

public:
    static shared_ptr<StatementParser> getStatementParser(Tokens& tokens);

private:
    static bool checkKeywordType(
        Tokens& tokens,
        string statementType,
        bool hasParenthesis);
    static bool checkAssignment(
        Tokens& tokens);
};