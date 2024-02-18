#include "Parser.h"
#include "ProcedureParser.h"

shared_ptr<Program> Parser::parseSource(vector<shared_ptr<Token>>& tokens) {
    shared_ptr<Program> program = make_shared<Program>();
    auto procedureParser = make_shared<ProcedureParser>();
    while (!tokens.empty()) {
        try {
            shared_ptr<Procedure> procedure = procedureParser->parseEntity(tokens);
            program->addToProcedureList(procedure);
        }
        catch (SyntaxErrorException& e) {
            throw SyntaxErrorException(e.what());
        }
        catch (SemanticErrorException& e) {
            throw SemanticErrorException(e.what());
        }
    }

    return program;
}