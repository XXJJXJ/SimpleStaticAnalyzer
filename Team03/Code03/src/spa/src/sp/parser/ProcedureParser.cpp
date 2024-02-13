#include <string>

#include "ProcedureParser.h"

shared_ptr<Procedure> ProcedureParser::parseEntity(vector<shared_ptr<Token>> tokens) {
    string procedureName = extractProcedureName(tokens);
    tokens.erase(tokens.begin(), tokens.begin() + 3);
    shared_ptr<Procedure> procedure = make_shared<Procedure>(procedureName);
    while (!isEndOfProcedure(tokens)) {
        auto statementParser = StatementParserFactory::getStatementParser(tokens);
        statementParser->setProcedureName(procedureName);
        shared_ptr<Statement> statement = statementParser->parseEntity(tokens);
        tokens.erase(tokens.begin(), tokens.begin() + 3);
        procedure->addToStatementList(statement);
    }

    if (isEndOfProcedure(tokens)) {
        tokens.erase(tokens.begin());
    }

    return procedure;
}

std::string ProcedureParser::extractProcedureName(vector<shared_ptr<Token>> tokens) {
    shared_ptr<Token> token0 = tokens[0];
    shared_ptr<Token> token1 = tokens[1];
    shared_ptr<Token> token2 = tokens[2];

    if (token0->getValue() != "procedure") {
        throw SyntaxErrorException("A procedure should start with procedure");
    } else if (token1->getType() != TokenType::NAME) {
        throw SyntaxErrorException("A procedure should have a NAME");
    } else if (token2->getType() != TokenType::LEFT_BRACE) {
        throw SyntaxErrorException("A procedure should begin with a {");
    } else {
        return token1->getValue();
    }

}

bool ProcedureParser::isEndOfProcedure(vector<shared_ptr<Token>> tokens) {
    return tokens.front()->getValue() == "}";
}
