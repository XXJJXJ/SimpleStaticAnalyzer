#include <string>

#include "ProcedureParser.h"

shared_ptr<Procedure> ProcedureParser::parseEntity(Tokens& tokens) {
    string procedureName = extractProcedureName(tokens);
    tokens.erase(tokens.begin(), tokens.begin() + 3);
    shared_ptr<Procedure> procedure = make_shared<Procedure>(procedureName);
    while (!isEndOfProcedure(tokens)) {
        auto statementParser = StatementParserFactory::getStatementParser(tokens);
        statementParser->setProcedureName(procedureName);
        shared_ptr<Statement> statement = statementParser->parseEntity(tokens);
        procedure->addToStatementList(statement);
    }

    if (procedure->getStatementList().size() == 0) {
        throw SyntaxErrorException("Procedure block cannot be empty");
    }

    if (isEndOfProcedure(tokens)) {
        tokens.erase(tokens.begin());
    }
    else {
        throw SyntaxErrorException("Procedure is missing a }");
    }

    return procedure;
}

string ProcedureParser::extractProcedureName(Tokens& tokens) {
    shared_ptr<Token> token0 = tokens[0];
    shared_ptr<Token> token1 = tokens[1];
    shared_ptr<Token> token2 = tokens[2];

    if (token0->getValue() != "procedure") {
        throw SyntaxErrorException("A procedure should start with procedure");
    }
    else if (token1->getType() != TokenType::NAME) {
        throw SyntaxErrorException("A procedure should have a NAME");
    }
    else if (token2->getType() != TokenType::LEFT_BRACE) {
        throw SyntaxErrorException("A procedure should begin with a {");
    }
    else {
        return token1->getValue();
    }
}

bool ProcedureParser::isEndOfProcedure(Tokens& tokens) {
    if (tokens.size() > 0) {
        return tokens[0]->getType() == TokenType::RIGHT_BRACE;
    }
    else {
        return false;
    }
}
