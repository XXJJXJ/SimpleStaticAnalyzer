#include "Parser.h"
#include "ProcedureParser.h"

shared_ptr<Program> Parser::parseSource(Tokens &tokens) {
    shared_ptr<Program> program = make_shared<Program>();
    shared_ptr<ProcedureParser> procedureParser = make_shared<ProcedureParser>();
    while (!tokens.empty()) {
        try {
            shared_ptr<Procedure> procedure = procedureParser->parseEntity(tokens);
            program->addToProcedureList(procedure);
        }
        catch (SyntaxErrorException &e) {
            throw SyntaxErrorException(e.what());
        }
        catch (SemanticErrorException &e) {
            throw SemanticErrorException(e.what());
        }
    }

    if (program->getProcedureList().size() == 0) {
        throw SyntaxErrorException("Program should have at least 1 procedure");
    }

    return program;
}