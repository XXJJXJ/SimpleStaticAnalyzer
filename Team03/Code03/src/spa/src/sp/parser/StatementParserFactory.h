#pragma once

#include<deque>
#include<vector>
#include "StatementParser.h"
#include "PrintStatementParser.h"
#include "ReadStatementParser.h"

class StatementParserFactory {

public:
    static shared_ptr<StatementParser> getStatementParser(vector<shared_ptr<Token>> tokens);

private:
    static bool checkKeywordType(
        vector<shared_ptr<Token>> tokens,
        string_view statementType);
};